<?php

/* 
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

$user = $_SERVER['PHP_AUTH_USER'];
$pass = $_SERVER['PHP_AUTH_PW'];
$userTag = $_GET['user'];

$dbname = "garfield";
$host = "fsmi-db.fsmi.uni-karlsruhe.de";
$port = 5435;

if (isset($user) && !empty($user)) {

    $retVal['status'] = "no input (or buy id=0)";

    $find = $_GET['find'];
    $buy = $_GET['buy'];

    $db = new PDO('pgsql:host=' . $host . ';port=' . $port . ';dbname=' . $dbname, $user, $pass);
    $db->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_WARNING);

    if (isset($find) && !empty($find)) {

	$snacks = split(";", $find);
	$retVal = querySnacksForTerms($db, $snacks);
    } else if (isset($buy) && !empty($buy)) {
	$snacks = split(";", $buy);
	if (isset($userTag) && !empty($userTag)) {
	    $retVal = buySnacks($db, $userTag, $snacks);
	} else {
	    $retVal = buySnacks($db, $user, $snacks);
	}
    }

    header("Access-Control-Allow-Origin: *");

    echo json_encode($retVal);



} else {
    header("WWW-Authenticate: Basic realm=\"SmartMonitor API Access (Invalid Credentials for " . $_SERVER['PHP_AUTH_USER'] . ")\"");
    header("HTTP/1.0 401 Unauthorized");

    echo '{"status": "wrong user/password"}';
}

function querySnacksForTerms($db, $snacks) {

    $retVal['status'] = array();

    $retVal['find'] = array();


    $findQuery = "SELECT snacks.snack_id, snack_name, snack_price FROM garfield.snacks "
	    . "JOIN garfield.snacks_available ON snacks_available.snack_id=snacks.snack_id WHERE snack_available "
	    . "AND (snack_name ILIKE :p1 OR snack_barcode LIKE :p2)";

    $stm = $db->prepare($findQuery);

    foreach ($snacks as $snack) {
	$retVal2 = querySnacks($stm, $snack);

	foreach ($retVal2['status'] as $val) {
	    $retVal['status'][] = $val;
	}
	foreach ($retVal2['find'] as $val) {
	    $retVal['find'][] = $val;
	}
    }
    return $retVal;
}

function querySnacks($stm, $snack) {

	$retVal['status'] = array();
    $retVal['find'] = array();

    $snack = "%" . $snack . "%";

	$retVal['status'][] = $stm->execute(array(
	':p1' => $snack,
	    ':p2' => $snack
	));

	$retVal['find'] = $stm->fetchAll(PDO::FETCH_ASSOC);
    $stm->closeCursor();
	return $retVal;
    }

function buySnacks($db, $user, $snacks) {
    $sqlBuy = "SELECT garfield.snack_buy(?::integer, ?::integer)";
    $sqlUser = "SELECT user_id FROM garfield.users WHERE user_name = ?";
    $sqlData = "SELECT snack_id, snack_name, snack_name, snack_price FROM garfield.snacks WHERE snack_id=?::integer";
    $buyStm = $db->prepare($sqlBuy);
    $userStm = $db->prepare($sqlUser);
    $dataStm = $db->prepare($sqlData);

    $retVal['status'] = array();
    $retVal['output'] = array();
    $retVal['data'] = array();

    foreach ($snacks as $id) {
	$retVal['data'][] = getData($dataStm, $id);
	$userID = getUserID($userStm, $user);
	$retVal2 = buySnack($buyStm, $userID['user_id'], $id);
	$retVal['status'][] = $retVal2['status'];

	$retVal['output'][] = $retVal2['output'];
    }

    $retVal['user'] = $user;
    return $retVal;
}

function getUserID($stm, $user) {
    $stm->execute(array($user));

    $out = $stm->fetch();
    $stm->closeCursor();
    return $out;
}

function buySnack($stm, $userID, $id) {

    $retVal['status'] = $stm->execute(array($userID, $id));

    $retVal['output'] = $stm->errorInfo();

    $stm->closeCursor();

    return $retVal;
}

function getData($stm, $id) {

    $stm->execute(array($id));

    $data = $stm->fetch(PDO::FETCH_ASSOC);
    $stm->closeCursor();
    return $data;
}
