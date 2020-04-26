using System;
using System.Collections.Generic;
using System.Text;
using System.Net.Http;
using TodoList.Persistence;
using System.Threading.Tasks;
using Microsoft.AspNetCore.WebUtilities;

namespace TodoList.Client.Model
{
    public class APIService
    {
        private HttpClient _client;

        public APIService(String uri)
        {
            _client = new HttpClient
            {
                BaseAddress = new Uri(uri)
            };
        }

        public async Task<List<List>> GetListsAsync()
        {
            var listsResponse = await _client.GetAsync("api/Lists");

            try
            {
                var lists =  await listsResponse.Content.ReadAsAsync<List<List>>();
                return lists;
            }
            catch (Exception)
            {
                throw new Exception("Bad request");
            }
        }

        public async Task<List<Item>> GetItemsByListIdAsync(Int32 listId)
        {
            var itemsResponse = await _client.GetAsync(
                QueryHelpers.AddQueryString("api/Items", new Dictionary<String, String>() 
                {
                    { "listId", listId.ToString() }
                }));

            try
            {
                var items = itemsResponse.Content.ReadAsAsync<List<Item>>();
                return items.Result;
            }
            catch (Exception)
            {
                throw new Exception("Bad request");
            }
        }
    }
}
