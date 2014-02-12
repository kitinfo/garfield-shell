/* 
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

var url = "db.php?";
var limitTag = "limitSpinner";
var tableBody = "logTBody";
var userList = new Array();

var TYPES = {
    SNACK_BUY: "Snackkauf",
    TRANSFER: "Transfer",
    DEPOSIT: "Aufladung",
    WITHDRAWAL: "Abbuchung",
    OPENING_VALUE: "Eröffnungsstand",
    PRINTER_ACCOUNTING: "Druck"
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
 Make an asynchronous GET request
 Calls /readyfunc/ with the request as parameter upon completion (readyState == 4)
 */
function asyncGet(url, readyfunc, errfunc, user, pass) {
    var request = new this.ajaxRequest();
    request.onreadystatechange =
	    function() {
		if (request.readyState == 4) {
		    if (request.status == 200) {
			readyfunc(request);
		    } else {
			errfunc(request);
		    }
		}
	    };

    request.open("GET", url, true, user, pass);
    try {
	request.send(null);
    }
    catch (e) {
	errfunc(e);
    }

    return request;
}

function refresh() {

    var limit = document.getElementById(limitTag);

    var xhr = asyncGet(url + "userlog=" + limit.value, function(xhr) {
	var response = JSON.parse(xhr.response);
	document.getElementById('status').textContent = response.status[0];

	buildLog(response.log);

	var balance = response.balance.balance.toFixed(2);

	document.getElementById("balance").textContent = balance;
	if (balance < 0) {
	    document.getElementById("balance").classList.add("red");
	}

	getUserNames();
    });

}


function getUserNames() {

    var userTags = document.getElementsByClassName('colUser');

    [].forEach.call(userTags, function(val) {

	if (!Number.isNaN(val.textContent)) {
	    if (userList[val.textContent]) {
		val.textContent = userList[val.textContent];
	    } else {
		val.textContent = getUserNameFromTag(val.textContent);
	    }
	}
    });
}

function getUserNameFromTag(val) {
    var xhr = syncGet(url + "usersearch=" + val);

    var response = JSON.parse(xhr.response);
    userList[val] = response.name;
    return response.name;
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

	var userCol = document.createElement('td');
	userCol.classList.add('colUser');
	userCol.textContent = val.pid;
	row.appendChild(userCol);

	var nameCol = document.createElement('td');
	nameCol.classList.add('colName');
	nameCol.textContent = val.desc;
	row.appendChild(nameCol);

	var typeCol = document.createElement('td');
	typeCol.classList.add('colType');
	typeCol.textContent = getType(val.type);
	row.appendChild(typeCol);

	var priceCol = document.createElement('td');
	priceCol.classList.add('colPrice');
	if (val.balance < 0) {
	    row.classList.add('red');
	}
	priceCol.textContent = val.balance.toFixed(2);
	row.appendChild(priceCol);
	

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