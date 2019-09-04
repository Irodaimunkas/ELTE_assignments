using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MaciLaci.Persistence
{
    public class MapLoad : IMapLoad
    {
        public void LoadMap(string path, FieldTable table)
        {
            using (StreamReader reader = new StreamReader(path)) // open file
            {
                String line = reader.ReadLine();
                String[] numbers = line.Split(' '); // reading a line, splitting on spaces
                Int32 tableSize = Int32.Parse(numbers[0]); // reading table size
                table.SetMaxScore(Int32.Parse(numbers[1])); // reading max score
                Int32 enemyMax = Int32.Parse(numbers[2]); // reading enemies number
                table.SetTableSize(tableSize);
                table.SetEnemiesSize(enemyMax);
                Int32 counter = 0; //enemy counter

                for (Int32 i = 0; i < tableSize; i++)
                {
                    line = reader.ReadLine();
                    numbers = line.Split(' ');

                    for (Int32 j = 0; j < tableSize; j++)
                    {
                        //setting map's layout
                        table.SetValue(i, j, Int32.Parse(numbers[j]));
                        //2 represents enemies
                        if (table[i, j] == 2)
                        {
                            table.Enemy(counter).setXY(i, j);
                            counter++;
                        }
                    }
                }

                counter = 0;
                //last line is setting enemies movement direction
                line = reader.ReadLine();
                numbers = line.Split(' ');
                //could have used enemyMax instead of numbers.Length, but fine either way
                for (int i = 0; i < numbers.Length; i++)
                {
                    table.Enemy(counter).SetDir(Int32.Parse(numbers[i]));
                    if (table.Enemy(counter).Dir == 7) table.Enemy(counter).SetLRUP('r');
                    else table.Enemy(counter).SetLRUP('u');
                    counter++;
                }
            }
        }
    }
}
