<?php

require_once("fileio.php");
require_once("database.php");

session_start();

if (isset($_POST['logout']) || !isset($_SESSION["account"])) {
    unset($_SESSION['account']);
    header("Location: index.php");
}

$maps = load_from_json("maps.json");

$currMap = [];
foreach ($maps as $map) {
    if ($map["name"] == $_GET["currMap"]) {
        $currMap = $map;
    }
}

$mapSols = lekerdezes($kapcsolat, 'SELECT * FROM mapSolBead2');
$mapUsers = lekerdezes($kapcsolat, 'SELECT * FROM mapUsersBead2');

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
        var currMap = <?php echo json_encode($currMap) ?>;
    </script>
    <script type="text/javascript" src="ajax.js"></script>
    <script type="text/javascript" src="walle3.js"></script>
</head>

<body>
    <div class="container-fluid">
        <h1>Wall-E - Welcome: <?= $_SESSION['account']['accountName']; ?></h1>
        <div class="row-fluid">
            <div id="game">
                <table id="game-table" class="table table-bordered">

                </table>
                <br>
                <table id="inputs-table" class="table table-bordered inputs">

                </table>
                <br>
                <table id="comms-table" class="table table-bordered comms">

                </table>
                <p id="time"></p>
                <input class="btn" id="new-game" type="button" value="New Game">
            </div>
        </div>

        <div class="row-fluid" id="random-ass-div">
            <h1 class="invisible" id="winners-header">Winners of this map:</h1>
            <table id="winners-table">

            </table>
        </div>

        <form action="" method="post">
            <input class="btn" type="submit" value="Logout" name="logout">
        </form>
    </div>
</body>

</html>