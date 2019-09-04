<?php

require_once("fileio.php");
require_once("database.php");

session_start();

if (isset($_POST['logout']) || !isset($_SESSION["account"])) {
    var_dump($_SESSION);
    unset($_SESSION['account']);
    header("Location: index.php");
}

$maps = load_from_json("maps.json");
$mapSols = lekerdezes($kapcsolat, 'SELECT * FROM mapSolBead2');
$mapUsers = lekerdezes($kapcsolat, 'SELECT * FROM mapUsersBead2');

if (isset($_POST["newMapName"])) {
    $myMap = json_decode($_POST["newMapName"], true);
    $thingie = true;
    foreach ($maps as $map) {
        if ($map["name"] == $myMap["name"]) {
            $thingie = false;
        }
    }
    if ($thingie) {
        array_push($maps, $myMap);
        save_to_json("maps.json", $maps);
        vegrehajtas(
            $kapcsolat,
            "INSERT INTO `mapSolBead2` (`name`, `numberOfSolutions`) 
        values (:mapName, 0)",
            [
                ":mapName"   => $myMap["name"],
            ]
        );
    }
}

if(isset($_POST["deleteName"])){
    foreach($maps as $map){
        if($map["name"] == $_POST["deleteName"]){
            $newMaps = [];
            foreach($maps as $map2){
                if($map2["name"] != $_POST["deleteName"]){
                    array_push($newMaps, $map2);
                }
            }
            save_to_json("maps.json", $newMaps);
            vegrehajtas($kapcsolat, 'DELETE FROM `mapSolBead2` WHERE `name` = :name', [ ":name" => $_POST["deleteName"] ]);
            vegrehajtas($kapcsolat, 'DELETE FROM `mapUsersBead2` WHERE `mapName` = :name', [ ":name" => $_POST["deleteName"] ]);
            break;
        }
    }
}

if (isset($_GET["won"])) {
    $thingie = true;
    foreach ($mapUsers as $mapUser) {
        if (($mapUser["accountName"] == $_SESSION["account"]["accountName"]) && ($mapUser["mapName"] == $_GET["currMap"])) {
            $thingie = false;
        }
    }
    if ($thingie) {
        vegrehajtas($kapcsolat, 'INSERT INTO mapUsersBead2 (`mapName`, `accountName`) VALUES ( :mapName, :accountName )', [
            ":mapName" => $_GET["currMap"],
            ":accountName" => $_SESSION["account"]["accountName"]
        ]);
        vegrehajtas($kapcsolat, 'UPDATE `mapSolBead2` SET `numberOfSolutions` = (`numberOfSolutions` + 1) WHERE `name`= :name', [":name" => $_GET["currMap"]]);
    }
}
?>

<html>

<head>
    <meta charset="utf-8">
    <title>Wall-E</title>
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <!-- Bootstrap -->
    <link href="css/bootstrap.min.css" rel="stylesheet" media="screen">
    <link href="css/bootstrap-responsive.min.css" rel="stylesheet">
    <link href="css/mine.css" rel="stylesheet" media="screen">
    <script type="text/javascript" src="css/bootstrap-responsive.min.js"></script>
    <script>
        function $(id) {
            //return document.getElementById(id);
            return document.querySelector(id);
        }

        function init() {
            $(`#map-select`).addEventListener(`click`, redirectTo, false);
        }

        window.addEventListener(`load`, init);

        function redirectTo() {
            window.location.href = "game.php?currMap=" + event.target.parentNode.id;
        }
    </script>
</head>

<body>
    <div class="container-fluid">
        <h1>Wall-E - Welcome: <?= $_SESSION['account']['accountName']; ?></h1>
        <div class="row-fluid">
            <div id="map-select">
                <p>Pick a map: </p>
                <table class="table table-hover">
                    <thead>
                        <tr>
                            <th scope="col">Map Name</th>
                            <th scope="col">Difficulty</th>
                            <th scope="col">Number of solutions</th>
                            <th scope="col">Did user solve it?</th>
                        </tr>
                    </thead>
                    <tbody>
                        <?php foreach ($maps as $map) : ?>
                            <?php
                            $didIt = false;
                            foreach ($mapUsers as $mapUser) {
                                if ($mapUser["mapName"] == $map["name"]) {
                                    if ($mapUser["accountName"] == $_SESSION['account']['accountName']) {
                                        $didIt = true;
                                    }
                                }
                            }
                            $numberOfSolutions = 0;
                            foreach ($mapSols as $mapSol) {
                                if ($mapSol["name"] == $map["name"]) {
                                    $numberOfSolutions = $mapSol["numberOfSolutions"];
                                }
                            }
                            ?>
                            <tr id="<?= $map['name']; ?>">
                                <td><?= $map['name']; ?></td>
                                <td><?= $map['difficulty']; ?></td>
                                <td><?= $numberOfSolutions ?></td>
                                <td><?= $didIt ? "Yes" : "No"; ?></td>
                            </tr>
                        <?php endforeach; ?>
                    </tbody>
                </table>
            </div>
        </div>

        <form action="" method="post">
            <input class="btn" type="submit" value="Logout" name="logout">
        </form>

        <?php if ($_SESSION["account"]["accountName"] == "admin" && $_SESSION["account"]["email"] == "admin@admin.hu") : ?>
            <h1>Hey Admin!</h1>
            <h2>Map creator</h2>
            <form action="" method="post" id="newMapForm">
                <input type="submit" value="Submit"><br>
                <textarea form="newMapForm" name="newMapName" id="newMapId" rows="20" cols="60" style="width: auto">
        {
            "name": "smallMap",
            "difficulty" : "very_hard",
            "player": { "row": 3, "column": 3, "direction": "left" },
            "damage": { "row": 1, "column": 2 },
            "table": [
                "▩⮣→→⮧",
                "◼↑✹▩↓",
                "↑⮤←▩↓",
                "▩▩▩▩◼"
            ],
            "walls": [
                { "row": 3, "column": 3, "side": "right" }
            ],
            "time": 20000
        }
        </textarea>
                <p>Little help:</p>
                <ul>
                    <li>floor (▩)</li>
                    <li>conveyor belt (←,↑,→,↓,⮠,⮡,⮢,⮣,⮤,⮥,⮦,⮧)</li>
                    <li>rotatory (↺,↻)</li>
                    <li>pit (◼)</li>
                    <li>damage (✹)</li>
                    <li>indexing starts at 0</li>
                </ul>
            </form>
            <p>Example format: </p>
            <img src="example.png" alt="example for formas">
            
            <h2>Delete (Map Name needed):</h2>
            <form action="" method="post">
                <input type="text" name="deleteName" id="deleteId"><br>
                <input type="submit" value="Delete">
            </form>
        <?php endif; ?>
    </div>
</body>

</html>