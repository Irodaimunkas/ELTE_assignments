<?php

require_once("database.php");
require_once("validation.php");

function ellenoriz($kapcsolat, $email, $jelszo)
{
    $accounts = lekerdezes(
        $kapcsolat,
        "SELECT * FROM `usersBead2` WHERE `email` = :emailName",
        [":emailName" => $email]
    );
    if (count($accounts) === 1) {
        $account = $accounts[0];
        return password_verify($jelszo, $account["password"])
            ? $account
            : false;
    }
    return false;
}

function beleptet($account)
{
    $_SESSION["account"] = $account;
}

session_start();

$hibak = [];

if (count($_POST) > 0) {
    $email = $_POST["emailName"];
    $jelszo = $_POST["passwordName"];

    $account = ellenoriz($kapcsolat, $email, $jelszo);

    if ($account === false) {
        $hibak[0] = "Error: Not a user!";
    }

    if (count($hibak) === 0) {
        beleptet($account);
        header("Location: mapSelect.php");
        exit();
    }
}
?>

<!DOCTYPE html>
<html lang="en">

<html>

<head>
    <title>Wall-E</title>
</head>

<body>
    <img src="logo.png" alt="logo">
    <br>
    <a href="http://webprogramozas.inf.elte.hu/ebr/public/storage/tasks/hgfcxkfdubozn307/web2_bead1/">Trial</a>
    <p>Wall-E, the little robot on the lower level of a huge spaceship, works in the engine room. One day, the spacecraft gets into a meteor shower and one of the meteors pierces a hole on the spacecraft's body. The damage is so dangerous that the automatic protection system immediately closes this level, so people cannot enter the engine room. Only Wall-E is in the engine room to give instructions. However, Wall-E's memory is finite, so it can only memorize and execute 5 commands at a time. In addition, the meteor has also damaged the communication unit, so you can always select only 5 of the 9 random instructions. However, the terrain is difficult to navigate: what helped everyday work, it may even hinder progress here. In the machine room there are conveyors, rotors and pits that affect the robot's movement. Help Wall-E get to the place of damage in the engine room and repair it!</p>
    <h1>Login</h1>
    <?php if(count($hibak) > 0): ?>
        <ul>
            <?php foreach($hibak as $hiba): ?>
                <li><?php echo $hiba ?></li>
            <?php endforeach; ?>
        </ul>
    <?php endif; ?>
    <form action="" method="post">
        E-Mail: <input type="email" name="emailName" id="emailId" placeholder="asd@asd.ex" required><br>
        Password: <input type="password" name="passwordName" id="passwordId" required><br>
        <input type="submit" value="login">
    </form>
    <a href="register.php">Register</a>
</body>

</html>