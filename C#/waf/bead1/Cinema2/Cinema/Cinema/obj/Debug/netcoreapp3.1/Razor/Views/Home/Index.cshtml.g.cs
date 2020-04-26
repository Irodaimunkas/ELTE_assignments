#pragma checksum "C:\Users\gonda\Desktop\git\ELTE_assignments\C#\waf\bead1\Cinema2\Cinema\Cinema\Views\Home\Index.cshtml" "{ff1816ec-aa5e-4d10-87f7-6f4963833460}" "cf8af68bcf7d6c85aa50fbe0e3076b647b2fd817"
// <auto-generated/>
#pragma warning disable 1591
[assembly: global::Microsoft.AspNetCore.Razor.Hosting.RazorCompiledItemAttribute(typeof(AspNetCore.Views_Home_Index), @"mvc.1.0.view", @"/Views/Home/Index.cshtml")]
namespace AspNetCore
{
    #line hidden
    using System;
    using System.Collections.Generic;
    using System.Linq;
    using System.Threading.Tasks;
    using Microsoft.AspNetCore.Mvc;
    using Microsoft.AspNetCore.Mvc.Rendering;
    using Microsoft.AspNetCore.Mvc.ViewFeatures;
#nullable restore
#line 1 "C:\Users\gonda\Desktop\git\ELTE_assignments\C#\waf\bead1\Cinema2\Cinema\Cinema\Views\_ViewImports.cshtml"
using Cinema;

#line default
#line hidden
#nullable disable
#nullable restore
#line 2 "C:\Users\gonda\Desktop\git\ELTE_assignments\C#\waf\bead1\Cinema2\Cinema\Cinema\Views\_ViewImports.cshtml"
using Cinema.Models;

#line default
#line hidden
#nullable disable
    [global::Microsoft.AspNetCore.Razor.Hosting.RazorSourceChecksumAttribute(@"SHA1", @"cf8af68bcf7d6c85aa50fbe0e3076b647b2fd817", @"/Views/Home/Index.cshtml")]
    [global::Microsoft.AspNetCore.Razor.Hosting.RazorSourceChecksumAttribute(@"SHA1", @"88b38380ea0d4f64bad62cefdedd00944e4c52ec", @"/Views/_ViewImports.cshtml")]
    public class Views_Home_Index : global::Microsoft.AspNetCore.Mvc.Razor.RazorPage<IEnumerable<Cinema.Models.Screening>>
    {
        private static readonly global::Microsoft.AspNetCore.Razor.TagHelpers.TagHelperAttribute __tagHelperAttribute_0 = new global::Microsoft.AspNetCore.Razor.TagHelpers.TagHelperAttribute("class", new global::Microsoft.AspNetCore.Html.HtmlString("page-link"), global::Microsoft.AspNetCore.Razor.TagHelpers.HtmlAttributeValueStyle.DoubleQuotes);
        private static readonly global::Microsoft.AspNetCore.Razor.TagHelpers.TagHelperAttribute __tagHelperAttribute_1 = new global::Microsoft.AspNetCore.Razor.TagHelpers.TagHelperAttribute("asp-action", "Details", global::Microsoft.AspNetCore.Razor.TagHelpers.HtmlAttributeValueStyle.DoubleQuotes);
        private static readonly global::Microsoft.AspNetCore.Razor.TagHelpers.TagHelperAttribute __tagHelperAttribute_2 = new global::Microsoft.AspNetCore.Razor.TagHelpers.TagHelperAttribute("asp-controller", "Movies", global::Microsoft.AspNetCore.Razor.TagHelpers.HtmlAttributeValueStyle.DoubleQuotes);
        #line hidden
        #pragma warning disable 0649
        private global::Microsoft.AspNetCore.Razor.Runtime.TagHelpers.TagHelperExecutionContext __tagHelperExecutionContext;
        #pragma warning restore 0649
        private global::Microsoft.AspNetCore.Razor.Runtime.TagHelpers.TagHelperRunner __tagHelperRunner = new global::Microsoft.AspNetCore.Razor.Runtime.TagHelpers.TagHelperRunner();
        #pragma warning disable 0169
        private string __tagHelperStringValueBuffer;
        #pragma warning restore 0169
        private global::Microsoft.AspNetCore.Razor.Runtime.TagHelpers.TagHelperScopeManager __backed__tagHelperScopeManager = null;
        private global::Microsoft.AspNetCore.Razor.Runtime.TagHelpers.TagHelperScopeManager __tagHelperScopeManager
        {
            get
            {
                if (__backed__tagHelperScopeManager == null)
                {
                    __backed__tagHelperScopeManager = new global::Microsoft.AspNetCore.Razor.Runtime.TagHelpers.TagHelperScopeManager(StartTagHelperWritingScope, EndTagHelperWritingScope);
                }
                return __backed__tagHelperScopeManager;
            }
        }
        private global::Microsoft.AspNetCore.Mvc.TagHelpers.AnchorTagHelper __Microsoft_AspNetCore_Mvc_TagHelpers_AnchorTagHelper;
        #pragma warning disable 1998
        public async override global::System.Threading.Tasks.Task ExecuteAsync()
        {
#nullable restore
#line 2 "C:\Users\gonda\Desktop\git\ELTE_assignments\C#\waf\bead1\Cinema2\Cinema\Cinema\Views\Home\Index.cshtml"
  
    ViewData["Title"] = "Home Page";

#line default
#line hidden
#nullable disable
            WriteLiteral("\r\n<div class=\"text-center\">\r\n    <div class=\"row\">\r\n        <div class=\"col-2 h1\">\r\n            Just Released:\r\n        </div>\r\n");
#nullable restore
#line 11 "C:\Users\gonda\Desktop\git\ELTE_assignments\C#\waf\bead1\Cinema2\Cinema\Cinema\Views\Home\Index.cshtml"
         foreach (var movie in (ViewData["Movies"] as List<Movie>).OrderBy(i => i.PostTime).Take(5))
        {

#line default
#line hidden
#nullable disable
            WriteLiteral("            <div class=\"col-2\">\r\n                <img");
            BeginWriteAttribute("src", " src=\"", 384, "\"", 450, 1);
#nullable restore
#line 14 "C:\Users\gonda\Desktop\git\ELTE_assignments\C#\waf\bead1\Cinema2\Cinema\Cinema\Views\Home\Index.cshtml"
WriteAttributeValue("", 390, Url.Action("DisplayImage", "Movies", new { id = movie.Id }), 390, 60, false);

#line default
#line hidden
#nullable disable
            EndWriteAttribute();
            WriteLiteral(" width=\"100%\" />\r\n            </div>\r\n");
#nullable restore
#line 16 "C:\Users\gonda\Desktop\git\ELTE_assignments\C#\waf\bead1\Cinema2\Cinema\Cinema\Views\Home\Index.cshtml"
        }

#line default
#line hidden
#nullable disable
            WriteLiteral("    </div>\r\n    <br />\r\n");
#nullable restore
#line 19 "C:\Users\gonda\Desktop\git\ELTE_assignments\C#\waf\bead1\Cinema2\Cinema\Cinema\Views\Home\Index.cshtml"
     foreach (var screening in Model.OrderBy(i => i.StartTime))
    {

#line default
#line hidden
#nullable disable
            WriteLiteral("    ");
            __tagHelperExecutionContext = __tagHelperScopeManager.Begin("a", global::Microsoft.AspNetCore.Razor.TagHelpers.TagMode.StartTagAndEndTag, "cf8af68bcf7d6c85aa50fbe0e3076b647b2fd8175882", async() => {
                WriteLiteral("\r\n        <div class=\"row\">\r\n            <div class=\"col-7 h1\">\r\n");
#nullable restore
#line 24 "C:\Users\gonda\Desktop\git\ELTE_assignments\C#\waf\bead1\Cinema2\Cinema\Cinema\Views\Home\Index.cshtml"
                 foreach(var movie in (ViewData["Movies"] as List<Movie>))
                {
                    if(movie.Id == screening.MovieId)
                    {
                        

#line default
#line hidden
#nullable disable
#nullable restore
#line 28 "C:\Users\gonda\Desktop\git\ELTE_assignments\C#\waf\bead1\Cinema2\Cinema\Cinema\Views\Home\Index.cshtml"
                   Write(movie.Name);

#line default
#line hidden
#nullable disable
#nullable restore
#line 28 "C:\Users\gonda\Desktop\git\ELTE_assignments\C#\waf\bead1\Cinema2\Cinema\Cinema\Views\Home\Index.cshtml"
                                   ;
                        break;
                    }
                }

#line default
#line hidden
#nullable disable
                WriteLiteral("            </div>\r\n            <div class=\"col-5 h1\">\r\n                ");
#nullable restore
#line 34 "C:\Users\gonda\Desktop\git\ELTE_assignments\C#\waf\bead1\Cinema2\Cinema\Cinema\Views\Home\Index.cshtml"
           Write(screening.StartTime);

#line default
#line hidden
#nullable disable
                WriteLiteral("\r\n            </div>\r\n        </div>\r\n    ");
            }
            );
            __Microsoft_AspNetCore_Mvc_TagHelpers_AnchorTagHelper = CreateTagHelper<global::Microsoft.AspNetCore.Mvc.TagHelpers.AnchorTagHelper>();
            __tagHelperExecutionContext.Add(__Microsoft_AspNetCore_Mvc_TagHelpers_AnchorTagHelper);
            __tagHelperExecutionContext.AddHtmlAttribute(__tagHelperAttribute_0);
            __Microsoft_AspNetCore_Mvc_TagHelpers_AnchorTagHelper.Action = (string)__tagHelperAttribute_1.Value;
            __tagHelperExecutionContext.AddTagHelperAttribute(__tagHelperAttribute_1);
            __Microsoft_AspNetCore_Mvc_TagHelpers_AnchorTagHelper.Controller = (string)__tagHelperAttribute_2.Value;
            __tagHelperExecutionContext.AddTagHelperAttribute(__tagHelperAttribute_2);
            if (__Microsoft_AspNetCore_Mvc_TagHelpers_AnchorTagHelper.RouteValues == null)
            {
                throw new InvalidOperationException(InvalidTagHelperIndexerAssignment("asp-route-id", "Microsoft.AspNetCore.Mvc.TagHelpers.AnchorTagHelper", "RouteValues"));
            }
            BeginWriteTagHelperAttribute();
#nullable restore
#line 21 "C:\Users\gonda\Desktop\git\ELTE_assignments\C#\waf\bead1\Cinema2\Cinema\Cinema\Views\Home\Index.cshtml"
                                                                        WriteLiteral(screening.MovieId);

#line default
#line hidden
#nullable disable
            __tagHelperStringValueBuffer = EndWriteTagHelperAttribute();
            __Microsoft_AspNetCore_Mvc_TagHelpers_AnchorTagHelper.RouteValues["id"] = __tagHelperStringValueBuffer;
            __tagHelperExecutionContext.AddTagHelperAttribute("asp-route-id", __Microsoft_AspNetCore_Mvc_TagHelpers_AnchorTagHelper.RouteValues["id"], global::Microsoft.AspNetCore.Razor.TagHelpers.HtmlAttributeValueStyle.DoubleQuotes);
            await __tagHelperRunner.RunAsync(__tagHelperExecutionContext);
            if (!__tagHelperExecutionContext.Output.IsContentModified)
            {
                await __tagHelperExecutionContext.SetOutputContentAsync();
            }
            Write(__tagHelperExecutionContext.Output);
            __tagHelperExecutionContext = __tagHelperScopeManager.End();
            WriteLiteral("\r\n");
#nullable restore
#line 38 "C:\Users\gonda\Desktop\git\ELTE_assignments\C#\waf\bead1\Cinema2\Cinema\Cinema\Views\Home\Index.cshtml"
    }

#line default
#line hidden
#nullable disable
            WriteLiteral("</div>\r\n");
        }
        #pragma warning restore 1998
        [global::Microsoft.AspNetCore.Mvc.Razor.Internal.RazorInjectAttribute]
        public global::Microsoft.AspNetCore.Mvc.ViewFeatures.IModelExpressionProvider ModelExpressionProvider { get; private set; }
        [global::Microsoft.AspNetCore.Mvc.Razor.Internal.RazorInjectAttribute]
        public global::Microsoft.AspNetCore.Mvc.IUrlHelper Url { get; private set; }
        [global::Microsoft.AspNetCore.Mvc.Razor.Internal.RazorInjectAttribute]
        public global::Microsoft.AspNetCore.Mvc.IViewComponentHelper Component { get; private set; }
        [global::Microsoft.AspNetCore.Mvc.Razor.Internal.RazorInjectAttribute]
        public global::Microsoft.AspNetCore.Mvc.Rendering.IJsonHelper Json { get; private set; }
        [global::Microsoft.AspNetCore.Mvc.Razor.Internal.RazorInjectAttribute]
        public global::Microsoft.AspNetCore.Mvc.Rendering.IHtmlHelper<IEnumerable<Cinema.Models.Screening>> Html { get; private set; }
    }
}
#pragma warning restore 1591