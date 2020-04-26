using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;
using TodoList.Persistence;
using TodoList.Persistence.Services;

namespace ToDoList.API.Controllers
{
    [Route("api/[controller]")]
    [ApiController]
    public class ItemsController : ControllerBase
    {
        public readonly TodoListService _service;

        public ItemsController(TodoListService service)
        {
            _service = service;
        }

        public ActionResult<List<Item>> Get(Int32 listId)
        {
            var items = _service.GetItems()
                .Where(i => i.ListId == listId)
                .ToList();
            
            if(items.Count <= 0)
            {
                return NotFound();
            }
            
            return items;
        }
    }
}