/* 
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

var url = "db.php?";
var limitTag = "limitSpinner";
var tableBody = "logTBody";

var TYPES = {
    SNACK_BUY: "Snackkauf",
    TRANSFER: "Transfer",
    DEPOSIT: "Aufladung",
    WITHDRAWAL: "Abbuchung",
   OPENING_VALUE: "Eröffnungsstand"
};


/**
 Create a XHR Object.
 IE Compat code removed.
 */
function ajaxRequest() {
    if (window.XMLHttpRequest) {//every sane browser, ever.
	return new XMLHttpRequest();
    } else {
	return false;
    }
}


/**
 Perform a synchronous GET request
 This function does not do any error checking, so exceptions might
 be thrown.
 */
function syncGet(url, user, pass) {
    var request = new this.ajaxRequest();
    request.open("GET", url, false, user, pass);
    request.send(null);
    return request;
}

function refresh() {

    var limit = document.getElementById(limitTag);

    var xhr = syncGet(url + "userlog=" + limit.value);

    var response = JSON.parse(xhr.response);
    document.getElementById('status').textContent = response.status[0];

    buildLog(response.log);

}


function buildLog(log) {

    var tBody = document.getElementById(tableBody);
    tBody.innerHTML = "";

    log.forEach(function(val) {

	var row = document.createElement('tr');

	var timestampCol = document.createElement('td');
	timestampCol.classList.add('colTimestamp');
	timestampCol.textContent = val.timestamp;
	row.appendChild(timestampCol);

	var nameCol = document.createElement('td');
	nameCol.classList.add('colName');
	nameCol.textContent = val.desc;
	row.appendChild(nameCol);

	var priceCol = document.createElement('td');
	priceCol.classList.add('colPrice');
	priceCol.textContent = val.balance;
	row.appendChild(priceCol);

	var typeCol = document.createElement('td');
	typeCol.classList.add('colType');
	typeCol.textContent = getType(val.type);
	row.appendChild(typeCol);

	var userCol = document.createElement('td');
	userCol.classList.add('colUser');
	userCol.textContent = val.pid;
	row.appendChild(userCol);

	tBody.appendChild(row);
    });



}

function getType(typeID) {

    var type = "";

    Object.keys(TYPES).forEach(function(key) {
	if (typeID === key) {
	    type = TYPES[key];
	}
    });
    return type;
}