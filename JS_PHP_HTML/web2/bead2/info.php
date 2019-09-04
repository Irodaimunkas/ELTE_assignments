<?php
require_once("database.php");

$mapUsers = lekerdezes($kapcsolat, 'SELECT * FROM mapUsersBead2');

$ajaxBack = array();
foreach ($mapUsers as $mapUser) {
    if ($mapUser["mapName"] == $_GET["currMap"]) {
        array_push($ajaxBack, $mapUser["accountName"]);
    }
}
echo json_encode($ajaxBack);
?>