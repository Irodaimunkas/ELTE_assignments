// Please see documentation at https://docs.microsoft.com/aspnet/core/client-side/bundling-and-minification
// for details on configuring this project to bundle and minify static web assets.

// Write your JavaScript code.

var counter = 6;

function selectSeat(elem) {
    if (elem.value == "Free" && counter > 0) {
        elem.value = "Booked";
        elem.parentElement.style = "background-color: yellow; border: 1px solid black"
        counter--;
    } else if (elem.value == "Booked") {
        elem.value = "Free";
        elem.parentElement.style = "background-color: white; border: 1px solid black"
        counter++;
    }
    console.log(counter);
}

function resetSeatCounter() {
    counter = 6;
}