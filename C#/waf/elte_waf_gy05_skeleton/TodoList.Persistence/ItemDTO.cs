using System;
using System.Collections.Generic;
using System.Text;

namespace TodoList.Persistence
{
    class ItemDTO
    {
        public Int32 Id { get; set; }

        public String Name { get; set; }

        public String Description { get; set; }

        public DateTime Deadline { get; set; }

        public byte[] Image { get; set; }

        public Int32 ListId { get; set; }
    }
}
