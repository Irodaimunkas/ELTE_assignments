using System;
using System.Collections.Generic;
using System.Data.Entity;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Minesweeper.Persistence
{
    public class MinesweeperDbDataAccess : IMinesweeperDataAccess
    {
        private MinesweeperContext _context;

        /// <summary>
        /// Konstruktor.
        /// </summary>
        /// <param name="connection">Adatbázis connection string.</param>
        public MinesweeperDbDataAccess(String connection)
        {
            _context = new MinesweeperContext(connection);
            _context.Database.CreateIfNotExists(); // adatbázis séma létrehozása, ha nem létezik
        }

        public async Task<MinesweeperTable> LoadAsync(string path)
        {
            GameDb game = await _context.Games
                    .Include(g => g.Fields)
                    .SingleAsync(g => g.Name == path); // játék állapot lekérdezése
            MinesweeperTable table = new MinesweeperTable(game.MapSize); // játéktábla modell létrehozása

            table.CurrPlayer = game.Player;
            table.Size = game.MapSize;

            foreach (FieldDb field in game.Fields) // mentett mezők feldolgozása
            {
                table.Map[field.X, field.Y].fieldType = field.FieldType;
                table.Map[field.X, field.Y].value = field.Value;
                table.Map[field.X, field.Y].visible = field.Visibility;
            }

            return table;
        }

        public async Task SaveAsync(string path, MinesweeperTable gameTable)
        {
            // játékmentés keresése azonos névvel
            GameDb overwriteGame = await _context.Games
                .Include(g => g.Fields)
                .SingleOrDefaultAsync(g => g.Name == path);
            if (overwriteGame != null)
                _context.Games.Remove(overwriteGame); // törlés

            GameDb dbGame = new GameDb
            {
                Name = path,
                MapSize = gameTable.Size,
                Player = gameTable.CurrPlayer
            }; // új mentés létrehozása

            for (Int32 i = 0; i < gameTable.Size; i++)
            {
                for (Int32 j = 0; j < gameTable.Size; j++)
                {
                    FieldDb field = new FieldDb
                    {
                        X = i,
                        Y = j,
                        Value = gameTable.Map[i, j].value,
                        Visibility = gameTable.Map[i, j].visible,
                        FieldType = gameTable.Map[i, j].fieldType
                    };
                    dbGame.Fields.Add(field);
                }
            } // mezők mentése

            _context.Games.Add(dbGame); // mentés hozzáadása a perzisztálandó objektumokhoz
            await _context.SaveChangesAsync(); // mentés az adatbázisba
        }
        public async Task<ICollection<SaveEntry>> ListAsync()
        {
            return await _context.Games
                    .OrderByDescending(g => g.Time) // rendezés mentési idő szerint csökkenő sorrendben
                    .Select(g => new SaveEntry { Name = g.Name, Time = g.Time }) // leképezés: Game => SaveEntry
                    .ToListAsync();
        }
    }
}
