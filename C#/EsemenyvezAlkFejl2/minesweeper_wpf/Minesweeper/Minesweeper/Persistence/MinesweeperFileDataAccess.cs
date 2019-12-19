using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Minesweeper.Model;

namespace Minesweeper.Persistence
{
    public class MinesweeperFileDataAccess : IMinesweeperDataAccess
    {
        public async Task<MinesweeperTable> LoadAsync(string path)
        {
            using (StreamReader reader = new StreamReader(path)) // fájl megnyitása
            {
                String line = await reader.ReadLineAsync();
                MinesweeperTable table = new MinesweeperTable(Int32.Parse(line));
                line = await reader.ReadLineAsync();
                Enum.TryParse(line, out Player player);
                table.CurrPlayer = player;
                for (Int32 i = 0; i < table.Size; i++)
                {
                    for (Int32 j = 0; j < table.Size; j++)
                    {
                        line = await reader.ReadLineAsync();
                        String[] split;
                        split = line.Split(' ');
                        table.Map[i, j].value = Int32.Parse(split[0]);
                        Enum.TryParse(split[1], out FieldType fieldType);
                        table.Map[i, j].fieldType = fieldType;
                        table.Map[i, j].visible = Boolean.Parse(split[2]);
                    }
                }
                return table;
            }
        }

        public async Task SaveAsync(string path, MinesweeperTable gameTable)
        {
            using (StreamWriter writer = new StreamWriter(path)) // fájl megnyitása
            {
                await writer.WriteLineAsync(gameTable.Size.ToString());
                await writer.WriteLineAsync(gameTable.CurrPlayer.ToString());
                for (Int32 i = 0; i < gameTable.Size; i++)
                {
                    for (Int32 j = 0; j < gameTable.Size; j++)
                    {
                        await writer.WriteLineAsync(gameTable.Map[i, j].value.ToString() + " " + gameTable.Map[i, j].fieldType.ToString() + " " + gameTable.Map[i, j].visible.ToString());
                    }
                }
            }
        }
    }
}
