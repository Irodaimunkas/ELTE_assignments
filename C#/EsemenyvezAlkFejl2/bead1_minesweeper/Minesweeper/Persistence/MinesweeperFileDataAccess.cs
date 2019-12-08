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
    {/*
        public async Task LoadAsync(String path, Player player, Field[,] map, Int32 size)
        {
            using (StreamReader reader = new StreamReader(path)) // fájl megnyitása
            {
                String line = await reader.ReadLineAsync();
                size = Int32.Parse(line);
                line = await reader.ReadLineAsync();
                Enum.TryParse(line, out player);
                map = new Field[size, size];
                Console.WriteLine(size);
                for (Int32 i = 0; i < size; i++)
                {
                    for (Int32 j = 0; j < size; j++)
                    {
                        line = await reader.ReadLineAsync();
                        String[] split;
                        split = line.Split(' ');
                        map[i, j].value = Int32.Parse(split[0]);
                        Enum.TryParse(split[1], out map[i, j].fieldType);
                        map[i, j].visible = Boolean.Parse(split[2]);
                    }
                }
            }

        }
        */
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
        /*
        public async Task SaveAsync(String path, Player player, Field[,] map, Int32 size)
        {
            using (StreamWriter writer = new StreamWriter(path)) // fájl megnyitása
            {
                await writer.WriteLineAsync(size.ToString());
                await writer.WriteLineAsync(player.ToString());
                for(Int32 i = 0; i < size; i++)
                {
                    for(Int32 j = 0; j < size; j++)
                    {
                        await writer.WriteLineAsync(map[i, j].value.ToString() + " " + map[i, j].fieldType.ToString() + " " + map[i, j].visible.ToString());
                    }
                }
            }
        }
        */
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
