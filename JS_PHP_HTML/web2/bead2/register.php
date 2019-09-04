<?php

require_once("database.php");
require_once("validation.php");

function letezik($kapcsolat, $felhasznalonev)
{
    $felhasznalok = lekerdezes(
        $kapcsolat,
        "SELECT * FROM `usersBead2` WHERE `accountName` = :accountName",
        [":accountName" => $felhasznalonev]
    );
    return count($felhasznalok) === 1;
}

function regisztral($kapcsolat, $felhasznalonev, $jelszo, $email)
{
    $db = vegrehajtas(
        $kapcsolat,
        "INSERT INTO `usersBead2` (`accountName`, `password`, `email`) 
        values (:accountName, :password, :email)",
        [
            ":accountName"   => $felhasznalonev,
            ":password"           => password_hash($jelszo, PASSWORD_DEFAULT),
            ":email" => $email,
        ]
    );
    return $db === 1;
}



$hibak = [];
if (count($_POST) > 0) {
    $felhasznalonev = $_POST["accountName"];
    $jelszo = $_POST["passwordName"];
    $email = $_POST["emailName"];

    if (letezik($kapcsolat, $felhasznalonev)) {
        $hibak[] = "Existing user!";
    }

    if (count($hibak) === 0) {
        regisztral($kapcsolat, $felhasznalonev, $jelszo, $email);
        header("Location: index.php");
        exit();
    }
}
?>

<!DOCTYPE html>
<html lang="en">

<html>

<head>
    <title>Main Page</title>
</head>

<body>
    <img src="logo.png" alt="logo">
    <br>
    <a href="http://webprogramozas.inf.elte.hu/ebr/public/storage/tasks/hgfcxkfdubozn307/web2_bead1/">Trial</a>
    <h1>Register</h1>
    <form action="" method="post">
        Account Name: <input type="text" name="accountName" id="accountId" required><br>
        Password: <input type="password" name="passwordName" id="passwordId" required><br>
        E-Mail: <input type="email" name="emailName" id="emailId" placeholder="asd@asd.ex" required><br>
        <input type="submit" value="Register">
    </form>
    <a href="index.php">Login</a>
</body>

</html>