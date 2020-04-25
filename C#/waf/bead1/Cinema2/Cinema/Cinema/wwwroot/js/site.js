// Please see documentation at https://docs.microsoft.com/aspnet/core/client-side/bundling-and-minification
// for details on configuring this project to bundle and minify static web assets.

// Write your JavaScript code.

function selectSeat(elem) {
    if (elem.value == "Free") {
        elem.value = "Booked";
        elem.parentElement.style = "background-color: yellow; border: 1px solid black"
    } else {
        elem.value = "Free";
        elem.parentElement.style = "background-color: white; border: 1px solid black"
    }
}