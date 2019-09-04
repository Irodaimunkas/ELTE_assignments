function $(id) {
    //return document.getElementById(id);
    return document.querySelector(id);
}

function $$(id) {
    return document.querySelectorAll(id);
}

function init() {
    $(`#new-game`).addEventListener(`click`, newGame, false);
    $(`#inputs-table`).addEventListener(`click`, onInputsClick, false);
    createMap();
}

window.addEventListener(`load`, init);

var commList = [`⭢`, `⭢`, `⭢`, `⮆`, `⮆`, `⮆`, `⇶`, `⇶`, `⇶`, `⬏`, `⬏`, `⬏`, `⬎`, `⬎`, `⬎`, `⮌`, `⮌`, `⮌`, `⭠`, `⭠`, `⭠`];
var randComms = [];
var exeComms = [];
var timeout = null;
var end = false;
var timer = null;
var currMapIndex = 0;

function createMap() {
    end = false;
    $(`#new-game`).className = `btn visible`;
    $(`#game-table`).innerHTML = generateMapWithoutWalls(currMap);
    makeWalls(currMap);

    $(`#game-table`).className = `table table-bordered visible`;
    $(`#inputs-table`).className = `table table-bordered inputs visible`;
    $(`#comms-table`).className = `table table-bordered comms visible`;

    shuffle(commList);
    randComms = commList.slice(0, 9);

    $(`#inputs-table`).innerHTML = generateRandomInputs();

    //5 * 500 time of executing
    timeout = setTimeout(function () { fillExeComms(); }, currMap.time);
    timer = startTimer(currMap.time / 1000, $(`#time`));
}


function fillExeComms() {
    while (exeComms.length < 5) {
        shuffle(randComms);
        var thing = randComms[0];
        randComms = arrayRemoveOneVal(randComms, thing);
        exeComms.push(thing);
        $(`#inputs-table`).innerHTML = generateRandomInputs();
        $(`#comms-table`).innerHTML = generateComms();
    }
    executeCommands();
}

function startTimer(duration, display) {
    var timer = duration, minutes, seconds;

    minutes = parseInt(timer / 60, 10)
    seconds = parseInt(timer % 60, 10);

    minutes = minutes < 10 ? "0" + minutes : minutes;
    seconds = seconds < 10 ? "0" + seconds : seconds;

    display.innerHTML = "<b>Remaining time:</b> " + minutes + ":" + seconds;

    if (--timer < 0) {
        timer = duration;
    }

    duration--;

    return setInterval(function () {
        minutes = parseInt(timer / 60, 10)
        seconds = parseInt(timer % 60, 10);

        minutes = minutes < 10 ? "0" + minutes : minutes;
        seconds = seconds < 10 ? "0" + seconds : seconds;

        display.innerHTML = "<b>Remaining time:</b> " + minutes + ":" + seconds;

        if (--timer < 0) {
            timer = duration;
        }
    }, 1000);
}

function makeWalls(map) {
    for (var i = 0; i < map.walls.length; i++) {
        switch (map.walls[i].side) {
            case `up`:
                $(`#field` + map.walls[i].row + `-` + map.walls[i].column).className += ` up`;
                break;
            case `down`:
                $(`#field` + map.walls[i].row + `-` + map.walls[i].column).className += ` down`;
                break;
            case `left`:
                $(`#field` + map.walls[i].row + `-` + map.walls[i].column).className += ` left`;
                break;
            case `right`:
                $(`#field` + map.walls[i].row + `-` + map.walls[i].column).className += ` right`;
                break;
        }
    }
}

function generateRandomInputs() {
    inputsTable = ``;
    inputsTable += `<tr>`;
    for (var i = 0; i < randComms.length; i++) {
        inputsTable += `<td class="mine">` + randComms[i] + `</td>`;
    }
    inputsTable += `</tr>`;
    return inputsTable;
}

function generateMapWithoutWalls(map) {
    var table = ``;
    for (var i = 0; i < map.table.length; i++) {
        table += `<tr>`;
        for (var j = 0; j < map.table[0].length; j++) {
            if (i === map.player.row && j === map.player.column) {
                switch (map.player.direction) {
                    case `up`:
                        table += `<td class="robot mine" id=field` + i + `-` + j + `>⮙</td>`;
                        break;
                    case `down`:
                        table += `<td class="robot mine" id=field` + i + `-` + j + `>⮛</td>`;
                        break;
                    case `left`:
                        table += `<td class="robot mine" id=field` + i + `-` + j + `>⮘</td>`;
                        break;
                    case `right`:
                        table += `<td class="robot mine" id=field` + i + `-` + j + `>⮚</td>`;
                        break;
                }
            } else {
                switch (map.table[i][j]) {
                    case `▩`:
                        table += `<td class="field mine" id=field` + i + `-` + j + `>` + map.table[i][j] + `</td>`;
                        break;
                    case `↺`:
                    case `↻`:
                        table += `<td class="rotate mine" id=field` + i + `-` + j + `>` + map.table[i][j] + `</td>`;
                        break;
                    case `◼`:
                        table += `<td class="hole mine" id=field` + i + `-` + j + `>` + map.table[i][j] + `</td>`;
                        break;
                    case `✹`:
                        table += `<td class="damage mine" id=field` + i + `-` + j + `>` + map.table[i][j] + `</td>`;
                        break;
                    case `←`:
                    case `↑`:
                    case `→`:
                    case `↓`:
                    case `⮠`:
                    case `⮡`:
                    case `⮢`:
                    case `⮣`:
                    case `⮤`:
                    case `⮥`:
                    case `⮦`:
                    case `⮧`:
                        table += `<td class="conveyor mine" id=field` + i + `-` + j + `>` + map.table[i][j] + `</td>`;
                        break;
                }
            }
        }
        table += `</tr>`;
    }
    return table;
}

function generateComms() {
    commsTable = ``;
    commsTable += `<tr>`;
    for (var i = 0; i < exeComms.length; i++) {
        commsTable += `<td class="mine">` + exeComms[i] + `</td>`;
    }
    commsTable += `</tr>`;
    return commsTable;
}

function newGame() {
    window.location.href = "mapSelect.php";
}

function shuffle(a) {
    for (let i = a.length - 1; i > 0; i--) {
        const j = Math.floor(Math.random() * (i + 1));
        [a[i], a[j]] = [a[j], a[i]];
    }
    return a;
}

function onInputsClick() {
    if (!end) {
        var thing = event.target.innerHTML;
        randComms = arrayRemoveOneVal(randComms, thing);
        exeComms.push(thing);
        $(`#inputs-table`).innerHTML = generateRandomInputs();
        $(`#comms-table`).innerHTML = generateComms();
        if (exeComms.length === 5) {
            executeCommands();
        }
    }
}

function arrayRemoveOneVal(arr, value) {
    var l = true;
    var i = 0;
    while (l && i < arr.length) {
        if (arr[i] === value) {
            arr.splice(i, 1);
            l = false;
        }
        i++;
    }
    return arr;
}

function executeCommands(i = 0) {
    clearInterval(timer);
    $(`#time`).innerHTML = ``;
    clearTimeout(timeout);
    if (i < 5 && !end) {
        setTimeout(function () { executeCommands(i + 1); }, 500);
        $(`#comms-table`).innerHTML = `<tr><td class="mine">Current command: ` + exeComms[i] + `</td></tr>`;
        switch (exeComms[i]) {
            case `⭢`:
                switch (currMap.player.direction) {
                    case `up`:
                        var wall = checkWalls(`down`, `up`, 1, `vertical`, `negative`);

                        if (!wall && currMap.player.row - 1 >= 0) {
                            currMap.player.row -= 1;
                        }

                        moveMap();

                        if (currMap.table[currMap.player.row][currMap.player.column] === `◼`) {
                            lost();
                        }

                        if (currMap.player.row === currMap.damage.row && currMap.player.column === currMap.damage.column) {
                            won();
                        }
                        break;
                    case `down`:
                        var wall = checkWalls(`up`, `down`, 1, `vertical`, `positive`);
                        if (!wall && currMap.player.row + 1 < currMap.table.length) {
                            currMap.player.row += 1;
                        }

                        moveMap();

                        if (currMap.table[currMap.player.row][currMap.player.column] === `◼`) {
                            lost();
                        }

                        if (currMap.player.row === currMap.damage.row && currMap.player.column === currMap.damage.column) {
                            won();
                        }
                        break;
                    case `left`:
                        var wall = checkWalls(`right`, `left`, 1, `horizontal`, `negative`);
                        if (!wall && currMap.player.column - 1 >= 0) {
                            currMap.player.column -= 1;
                        }

                        moveMap();

                        if (currMap.table[currMap.player.row][currMap.player.column] === `◼`) {
                            lost();
                        }

                        if (currMap.player.row === currMap.damage.row && currMap.player.column === currMap.damage.column) {
                            won();
                        }
                        break;
                    case `right`:
                        var wall = checkWalls(`left`, `right`, 1, `horizontal`, `positive`);
                        if (!wall && currMap.player.column + 1 < currMap.table[0].length) {
                            currMap.player.column += 1;
                        }

                        moveMap();

                        if (currMap.table[currMap.player.row][currMap.player.column] === `◼`) {
                            lost();
                        }

                        if (currMap.player.row === currMap.damage.row && currMap.player.column === currMap.damage.column) {
                            won();
                        }
                        break;
                }
                break;
            case `⮆`:
                switch (currMap.player.direction) {
                    case `up`:
                        var wall = checkWalls(`down`, `up`, 2, `vertical`, `negative`);
                        if (!wall && currMap.player.row - 2 >= 0) {
                            currMap.player.row -= 2;
                        }

                        moveMap();

                        if (currMap.table[currMap.player.row][currMap.player.column] === `◼`) {
                            lost();
                        }

                        if (currMap.player.row === currMap.damage.row && currMap.player.column === currMap.damage.column) {
                            won();
                        }
                        break;
                    case `down`:
                        var wall = checkWalls(`up`, `down`, 2, `vertical`, `positive`);
                        if (!wall && currMap.player.row + 2 < currMap.table.length) {
                            currMap.player.row += 2;
                        }

                        moveMap();

                        if (currMap.table[currMap.player.row][currMap.player.column] === `◼`) {
                            lost();
                        }

                        if (currMap.player.row === currMap.damage.row && currMap.player.column === currMap.damage.column) {
                            won();
                        }
                        break;
                    case `left`:
                        var wall = checkWalls(`right`, `left`, 2, `horizontal`, `negative`);
                        if (!wall && currMap.player.column - 2 >= 0) {
                            currMap.player.column -= 2;
                        }

                        moveMap();

                        if (currMap.table[currMap.player.row][currMap.player.column] === `◼`) {
                            lost();
                        }

                        if (currMap.player.row === currMap.damage.row && currMap.player.column === currMap.damage.column) {
                            won();
                        }
                        break;
                    case `right`:
                        var wall = checkWalls(`left`, `right`, 2, `horizontal`, `positive`);
                        if (!wall && currMap.player.column + 2 < currMap.table[0].length) {
                            currMap.player.column += 2;
                        }

                        moveMap();

                        if (currMap.table[currMap.player.row][currMap.player.column] === `◼`) {
                            lost();
                        }

                        if (currMap.player.row === currMap.damage.row && currMap.player.column === currMap.damage.column) {
                            won();
                        }
                        break;
                }
                break;
            case `⇶`:
                switch (currMap.player.direction) {
                    case `up`:
                        var wall = checkWalls(`down`, `up`, 3, `vertical`, `negative`);
                        if (!wall && currMap.player.row - 3 >= 0) {
                            currMap.player.row -= 3;
                        }

                        moveMap();

                        if (currMap.table[currMap.player.row][currMap.player.column] === `◼`) {
                            lost();
                        }

                        if (currMap.player.row === currMap.damage.row && currMap.player.column === currMap.damage.column) {
                            won();
                        }
                        break;
                    case `down`:
                        var wall = checkWalls(`up`, `down`, 3, `vertical`, `positive`);
                        if (!wall && currMap.player.row + 3 < currMap.table.length) {
                            currMap.player.row += 3;
                        }

                        moveMap();

                        if (currMap.table[currMap.player.row][currMap.player.column] === `◼`) {
                            lost();
                        }

                        if (currMap.player.row === currMap.damage.row && currMap.player.column === currMap.damage.column) {
                            won();
                        }
                        break;
                    case `left`:
                        var wall = checkWalls(`right`, `left`, 3, `horizontal`, `negative`);
                        if (!wall && currMap.player.column - 3 >= 0) {
                            currMap.player.column -= 3;
                        }

                        moveMap();

                        if (currMap.table[currMap.player.row][currMap.player.column] === `◼`) {
                            lost();
                        }

                        if (currMap.player.row === currMap.damage.row && currMap.player.column === currMap.damage.column) {
                            won();
                        }
                        break;
                    case `right`:
                        var wall = checkWalls(`left`, `right`, 3, `horizontal`, `positive`);
                        if (!wall && currMap.player.column + 3 < currMap.table[0].length) {
                            currMap.player.column += 3;
                        }

                        moveMap();

                        if (currMap.table[currMap.player.row][currMap.player.column] === `◼`) {
                            lost();
                        }

                        if (currMap.player.row === currMap.damage.row && currMap.player.column === currMap.damage.column) {
                            won();
                        }
                        break;
                }
                break;
            case `⬏`:
                switch (currMap.player.direction) {
                    case `up`:
                        currMap.player.direction = `left`;
                        break;
                    case `down`:
                        currMap.player.direction = `right`;
                        break;
                    case `left`:
                        currMap.player.direction = `down`;
                        break;
                    case `right`:
                        currMap.player.direction = `up`;
                        break;
                }
                break;
            case `⬎`:
                switch (currMap.player.direction) {
                    case `up`:
                        currMap.player.direction = `right`;
                        break;
                    case `down`:
                        currMap.player.direction = `left`;
                        break;
                    case `left`:
                        currMap.player.direction = `up`;
                        break;
                    case `right`:
                        currMap.player.direction = `down`;
                        break;
                }
                break;
            case `⮌`:
                switch (currMap.player.direction) {
                    case `up`:
                        currMap.player.direction = `down`;
                        break;
                    case `down`:
                        currMap.player.direction = `up`;
                        break;
                    case `left`:
                        currMap.player.direction = `right`;
                        break;
                    case `right`:
                        currMap.player.direction = `left`;
                        break;
                }
                break;
            case `⭠`:
                switch (currMap.player.direction) {
                    case `up`:
                        var wall = checkWalls(`up`, `down`, 1, `vertical`, `positive`);
                        if (!wall && currMap.player.row + 1 < currMap.table.length) {
                            currMap.player.row += 1;
                        }

                        moveMap();

                        if (currMap.table[currMap.player.row][currMap.player.column] === `◼`) {
                            lost();
                        }

                        if (currMap.player.row === currMap.damage.row && currMap.player.column === currMap.damage.column) {
                            won();
                        }
                        break;
                    case `down`:
                        var wall = checkWalls(`down`, `up`, 1, `vertical`, `negative`);
                        if (!wall && currMap.player.row - 1 >= 0) {
                            currMap.player.row -= 1;
                        }

                        moveMap();

                        if (currMap.table[currMap.player.row][currMap.player.column] === `◼`) {
                            lost();
                        }

                        if (currMap.player.row === currMap.damage.row && currMap.player.column === currMap.damage.column) {
                            won();
                        }
                        break;
                    case `left`:
                        var wall = checkWalls(`left`, `right`, 1, `horizontal`, `positive`);
                        if (!wall && currMap.player.column + 1 < currMap.table[0].length) {
                            currMap.player.column += 1;
                        }

                        moveMap();

                        if (currMap.table[currMap.player.row][currMap.player.column] === `◼`) {
                            lost();
                        }

                        if (currMap.player.row === currMap.damage.row && currMap.player.column === currMap.damage.column) {
                            won();
                        }
                        break;
                    case `right`:
                        var wall = checkWalls(`right`, `left`, 1, `horizontal`, `negative`);
                        if (!wall && currMap.player.column - 1 >= 0) {
                            currMap.player.column -= 1;
                        }

                        moveMap();

                        if (currMap.table[currMap.player.row][currMap.player.column] === `◼`) {
                            lost();
                        }

                        if (currMap.player.row === currMap.damage.row && currMap.player.column === currMap.damage.column) {
                            won();
                        }
                        break;
                }
                break;
        }

        $(`#game-table`).innerHTML = generateMapWithoutWalls(currMap);
        makeWalls(currMap);
    } else {
        exeComms = []
        $(`#comms-table`).innerHTML = ``;

        shuffle(commList);
        randComms = commList.slice(0, 9);

        $(`#inputs-table`).innerHTML = generateRandomInputs();
    }
    if (exeComms.length === 0 && !end) {
        timeout = setTimeout(function () { fillExeComms(); }, currMap.time);
        timer = startTimer(currMap.time / 1000, $(`#time`));
    }
}

function lost() {
    clearInterval(timer);
    clearTimeout(timeout);
    end = true;
    $('#random-ass-div').innerHTML = `<h1>You lost!</h1>`;
    //window.location.href = "mapSelect.php?lost=true";
}

function won() {
    clearInterval(timer);
    clearTimeout(timeout);
    end = true;
    //window.location.href = "mapSelect.php?won=true&currMap=" + currMap["name"];
    ajax({
        url: 'mapSelect.php',
        getadat: 'won=true&currMap=' + currMap["name"],
    });
    ajax({
        url: 'info.php',
        getadat: 'won=true&currMap=' + currMap["name"],
        siker: function (xhr, data) {
            infoTolto(xhr, data);
        },
    });
}

function infoTolto(xhr, data) {
    var dataParsed = JSON.parse(data);
    $('#winners-header').className = "visible";
    $('#winners-table').innerHTML += `<tr>`;
    for (var j = 0; j < dataParsed.length; j++) {
        $('#winners-table').innerHTML += `<td>`;
        $('#winners-table').innerHTML += dataParsed[j];
        $('#winners-table').innerHTML += `</td>`;
    }
    $('#winners-table').innerHTML += `</tr>`;
}

function checkWalls(oppositeWall, mainWall, k, verticality, pos) {
    var l = false
    for (var j = 0; j < currMap.walls.length; j++) {
        if (verticality === `horizontal`) {
            if (pos === `positive`) {
                for (var i = 1; i < k + 1; i++) {
                    if (currMap.player.row === currMap.walls[j].row &&
                        currMap.player.column + i === currMap.walls[j].column &&
                        currMap.walls[j].side === oppositeWall) {
                        l = true;
                    }
                }
                for (var i = 0; i < k; i++) {
                    if (currMap.player.row === currMap.walls[j].row &&
                        currMap.player.column + i === currMap.walls[j].column &&
                        currMap.walls[j].side === mainWall) {
                        l = true;
                    }
                }
            } else {
                for (var i = 1; i < k + 1; i++) {
                    if (currMap.player.row === currMap.walls[j].row &&
                        currMap.player.column - i === currMap.walls[j].column &&
                        currMap.walls[j].side === oppositeWall) {
                        l = true;
                    }
                }
                for (var i = 0; i < k; i++) {
                    if (currMap.player.row === currMap.walls[j].row &&
                        currMap.player.column - i === currMap.walls[j].column &&
                        currMap.walls[j].side === mainWall) {
                        l = true;
                    }
                }
            }
        } else {
            if (pos === `positive`) {
                for (var i = 1; i < k + 1; i++) {
                    if (currMap.player.row + i === currMap.walls[j].row &&
                        currMap.player.column === currMap.walls[j].column &&
                        currMap.walls[j].side === oppositeWall) {
                        l = true;
                    }
                }
                for (var i = 0; i < k; i++) {
                    if (currMap.player.row + i === currMap.walls[j].row &&
                        currMap.player.column === currMap.walls[j].column &&
                        currMap.walls[j].side === mainWall) {
                        l = true;
                    }
                }
            } else {
                for (var i = 1; i < k + 1; i++) {
                    if (currMap.player.row - i === currMap.walls[j].row &&
                        currMap.player.column === currMap.walls[j].column &&
                        currMap.walls[j].side === oppositeWall) {
                        l = true;
                    }
                }
                for (var i = 0; i < k; i++) {
                    if (currMap.player.row - i === currMap.walls[j].row &&
                        currMap.player.column === currMap.walls[j].column &&
                        currMap.walls[j].side === mainWall) {
                        l = true;
                    }
                }
            }
        }
    }
    return l;
}

function moveMap() {
    var endMap = false;
    do {
        switch (currMap.table[currMap.player.row][currMap.player.column]) {
            case `←`:
            case `⮠`:
            case `⮢`:
                if (currMap.player.column - 1 >= 0) {
                    currMap.player.column -= 1;
                    switch (currMap.table[currMap.player.row][currMap.player.column]) {
                        case `⮠`:
                            rotate(`right`);
                            break;
                        case `⮡`:
                            rotate(`left`);
                            break;
                        case `⮢`:
                            rotate(`left`);
                            break;
                        case `⮣`:
                            rotate(`right`);
                            break;
                        case `⮤`:
                            rotate(`right`);
                            break;
                        case `⮥`:
                            rotate(`left`);
                            break;
                        case `⮦`:
                            rotate(`left`);
                            break;
                        case `⮧`:
                            rotate(`right`);
                            break;
                    }
                } else {
                    endMap = true;
                }
                break;
            case `↑`:
            case `⮤`:
            case `⮥`:
                if (currMap.player.row - 1 >= 0) {
                    currMap.player.row -= 1;
                    switch (currMap.table[currMap.player.row][currMap.player.column]) {
                        case `⮠`:
                            rotate(`right`);
                            break;
                        case `⮡`:
                            rotate(`left`);
                            break;
                        case `⮢`:
                            rotate(`left`);
                            break;
                        case `⮣`:
                            rotate(`right`);
                            break;
                        case `⮤`:
                            rotate(`right`);
                            break;
                        case `⮥`:
                            rotate(`left`);
                            break;
                        case `⮦`:
                            rotate(`left`);
                            break;
                        case `⮧`:
                            rotate(`right`);
                            break;
                    }
                } else {
                    endMap = true;
                }
                break;
            case `→`:
            case `⮡`:
            case `⮣`:
                if (currMap.player.column + 1 < currMap.table[0].length) {
                    currMap.player.column += 1;
                    switch (currMap.table[currMap.player.row][currMap.player.column]) {
                        case `⮠`:
                            rotate(`right`);
                            break;
                        case `⮡`:
                            rotate(`left`);
                            break;
                        case `⮢`:
                            rotate(`left`);
                            break;
                        case `⮣`:
                            rotate(`right`);
                            break;
                        case `⮤`:
                            rotate(`right`);
                            break;
                        case `⮥`:
                            rotate(`left`);
                            break;
                        case `⮦`:
                            rotate(`left`);
                            break;
                        case `⮧`:
                            rotate(`right`);
                            break;
                    }
                } else {
                    endMap = true;
                }
                break;
            case `↓`:
            case `⮦`:
            case `⮧`:
                if (currMap.player.row + 1 < currMap.table.length) {
                    currMap.player.row += 1;
                    switch (currMap.table[currMap.player.row][currMap.player.column]) {
                        case `⮠`:
                            rotate(`right`);
                            break;
                        case `⮡`:
                            rotate(`left`);
                            break;
                        case `⮢`:
                            rotate(`left`);
                            break;
                        case `⮣`:
                            rotate(`right`);
                            break;
                        case `⮤`:
                            rotate(`right`);
                            break;
                        case `⮥`:
                            rotate(`left`);
                            break;
                        case `⮦`:
                            rotate(`left`);
                            break;
                        case `⮧`:
                            rotate(`right`);
                            break;
                    }
                } else {
                    endMap = true;
                }
                break;
        }
    } while (
        (currMap.table[currMap.player.row][currMap.player.column] === `←` ||
            currMap.table[currMap.player.row][currMap.player.column] === `↑` ||
            currMap.table[currMap.player.row][currMap.player.column] === `→` ||
            currMap.table[currMap.player.row][currMap.player.column] === `↓` ||
            currMap.table[currMap.player.row][currMap.player.column] === `⮠` ||
            currMap.table[currMap.player.row][currMap.player.column] === `⮡` ||
            currMap.table[currMap.player.row][currMap.player.column] === `⮢` ||
            currMap.table[currMap.player.row][currMap.player.column] === `⮣` ||
            currMap.table[currMap.player.row][currMap.player.column] === `⮤` ||
            currMap.table[currMap.player.row][currMap.player.column] === `⮥` ||
            currMap.table[currMap.player.row][currMap.player.column] === `⮦` ||
            currMap.table[currMap.player.row][currMap.player.column] === `⮧`) &&
        (currMap.player.row >= 0 &&
            currMap.player.row < currMap.table.length &&
            currMap.player.column < currMap.table[0].length &&
            currMap.player.column >= 0) &&
        !endMap
    )

    switch (currMap.table[currMap.player.row][currMap.player.column]) {
        case `↺`:
            rotate(`left`);
            break;
        case `↻`:
            rotate(`right`);
            break;
    }
}

function rotate(dir) {
    switch (dir) {
        case `left`:
            switch (currMap.player.direction) {
                case `left`:
                    currMap.player.direction = `down`;
                    break;
                case `right`:
                    currMap.player.direction = `up`;
                    break;
                case `up`:
                    currMap.player.direction = `left`;
                    break;
                case `down`:
                    currMap.player.direction = `right`;
                    break;
            }
            break;
        case `right`:
            switch (currMap.player.direction) {
                case `left`:
                    currMap.player.direction = `up`;
                    break;
                case `right`:
                    currMap.player.direction = `down`;
                    break;
                case `up`:
                    currMap.player.direction = `right`;
                    break;
                case `down`:
                    currMap.player.direction = `left`;
                    break;
            }
            break;
    }
}