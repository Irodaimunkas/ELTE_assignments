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
    public class ListsController : ControllerBase
    {
        public readonly TodoListService _service;

        public ListsController(TodoListService service)
        {
            _service = service;
        }

        public ActionResult<List<List>> Get()
        {
            var lists = _service.GetLists()
                .ToList();

            return lists;
        }
    }
}