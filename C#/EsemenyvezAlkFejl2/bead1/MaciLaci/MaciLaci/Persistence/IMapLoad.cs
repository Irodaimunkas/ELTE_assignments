using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MaciLaci.Persistence
{
    public interface IMapLoad
    {
        void LoadMap(string path, FieldTable table);
    }
}
