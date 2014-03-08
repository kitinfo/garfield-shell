function getURLPath(user) {
	var path = location.pathname.split('/');
	path.pop();
	path = location.protocol + "//" + user + location.host + path.join("/") + "/db.php?";
	return path;
}

var url = getURLPath("");
var findData = new Array();
var cartData = new Array();

document.getElementById("logout").setAttribute('href', getURLPath("d@"));

/**
 * search on database and inputs this in the table
 */
function searchRequest() {

    var search = document.getElementById('findString').value;

    var request = syncGet(url + "find=" + search);

    var response = JSON.parse(request.response, true);

    if (!checkStatus(response)) {
	return;
    }

    var tbody = document.getElementById('tableBody');
    tbody.innerHTML = "";
    findData = response.find;

    findData.forEach(function(data) {

	var item = document.createElement('tr');

	var checkBoxItem = document.createElement('td');
	var checkBox = document.createElement('input');
	checkBox.setAttribute('type', 'checkbox');
	checkBox.setAttribute('checked', 'checked');
	checkBox.setAttribute('id', 'checkbox' + data.snack_id);
	checkBox.setAttribute('class', 'checkboxAll');

	checkBoxItem.appendChild(checkBox);
	item.appendChild(checkBoxItem);

	item = buildBaseTable(item, data, 'find');

	tbody.appendChild(item);
    });

    calcFindPrice();
}


function checkStatus(response) {

    document.getElementById('status').textContent = response.status;

    if (response.status == true || response.status[0] == true) {
	return true;
    }

    return false;
}

function searchIDRequest(id) {

    if (findData[id]) {
	var val = findData[id];
    }
    else if (cartData[id]) {
	var val = cartData[id];
    }
    else {

    var request = syncGet(url + 'findid=' + id);

    var response = JSON.parse(request.response);

    if (!checkStatus(response)) {
	return;
    }

    if (response.find.length < 1) {
	document.getElementById('status').textContent = "No Entry found!";
	return;
	}
	var val = response.find[0];
    }

    addSingleToCart(val, 1);
}

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

/**
 *
 * sends a buy request to database
 */
function buyRequest(buy) {



    var user = document.getElementById('userField').value;

    var outUrl = url + "buy=";

    if (user == "") {
	outUrl += buy;
    } else {
	outUrl += buy + "&user=" + user;
    }

    var request = syncGet(outUrl);

    var response = JSON.parse(request.response);

    console.log(response['status']);
    console.log(response['output']);

    checkStatus(response);


    for (i = 0; i < response['status'].length; i++) {

	var row = buildDataRow(response['data'][i]);

	var userItem = document.createElement('td');
	userItem.textContent = response['user'];
	row.appendChild(userItem);

	var timeStamp = document.createElement('td');
	console.log(response['status'][i]);
	if (response['status'][i]) {
	    timeStamp.textContent = response['timestamp'][i].user_trans_log_timestamp;
	}
	row.appendChild(timeStamp);


	var item = document.createElement('td');
	if (response['status'][i] == false) {
	    item.textContent += response['output'][i][2];
	} else {
	    item.textContent = "OK";
	}
	row.appendChild(item);
	document.getElementById('tableBuyBody').appendChild(row);
    }



}

function buildDataRow(data) {
    var row = document.createElement('tr');

    var idItem = document.createElement('td');

    idItem.textContent = data.snack_id;
    row.appendChild(idItem);

    var nameItem = document.createElement('td');

    nameItem.textContent = data.snack_name;
    row.appendChild(nameItem);

    var priceItem = document.createElement('td');

    priceItem.textContent = data.snack_price;
    row.appendChild(priceItem);
    console.log(idItem);

    return row;
}


function toggleAll() {
    var checkboxes = document.getElementsByClassName('checkboxAll');
    if (document.getElementById("checkboxAll").checked == true) {


	for (var i = 0; i < checkboxes.length; i++) {
	    checkboxes[i].checked = true;
	}
    } else {
	for (var i = 0; i < checkboxes.length; i++) {
	    checkboxes[i].checked = false;
	}
    }

    calcPrice();
}

function calcPrice() {
    //TODO: calc prices
}

function buildBaseTable(tr, data, classTag) {

    var item = tr;


    var idItem = document.createElement('td');
    idItem.classList.add(classTag + "IDCol");
    idItem.textContent = data.snack_id;
    item.appendChild(idItem);

    var nameItem = document.createElement('td');
    nameItem.classList.add(classTag + "NameCol");
    nameItem.textContent = data.snack_name;
    item.appendChild(nameItem);

    var priceItem = document.createElement('td');
    priceItem.classList.add(classTag + "PriceCol");
    priceItem.textContent = data.snack_price;
    item.appendChild(priceItem);

    var counterItem = document.createElement('td');
    counterItem.classList.add(classTag + "CounterCol");
    var spinner = document.createElement('input');
    spinner.setAttribute('type', 'number');
    spinner.setAttribute('min', "0");
    spinner.setAttribute('step', "1");
    spinner.setAttribute('value', "1");
    spinner.setAttribute('id', classTag + 'Counter' + data.snack_id);
    counterItem.appendChild(spinner);

    item.appendChild(counterItem);

    return item;
}

function addToCart() {

    findData.forEach(function(val) {

	var checkbox = document.getElementById("checkbox" + val.snack_id);

	if (checkbox.checked) {

	    var counter = document.getElementById('findCounter' + val.snack_id);

	    if (counter.value !== "0") {

		addSingleToCart(val, counter.value);

	    }

	}

    });
    calcCartPrice();
}

function addSingleToCart(val, counter) {

    if (cartData[val.snack_id]) {
	var counterElem = document.getElementById('cartCounter' + val.snack_id);
	var counterCart = parseInt(counterElem.value);

	counterElem.value = counterCart + parseInt(counter);
    } else {


	var item = document.createElement('tr');

	item = buildBaseTable(item, val, 'cart');

	document.getElementById('cartTableBody').appendChild(item);

	document.getElementById('cartCounter' + val.snack_id).value = counter;

	cartData[val.snack_id] = val;
    }

}

function calcCartPrice() {

    var sumElem = document.getElementById('cartSum');

    var sum = 0.00;
    cartData.forEach(function(val) {
	sum += (val.snack_price * parseInt(document.getElementById('cartCounter' + val.snack_id).value));
    });
    sumElem.textContent = sum.toFixed(2);
}

function calcFindPrice() {

    var sumElem = document.getElementById('findSum');

    var sum = 0.00;
    findData.forEach(function(val) {
	if (document.getElementById('checkbox' + val.snack_id).checked) {
	    sum += (val.snack_price * parseInt(document.getElementById('findCounter' + val.snack_id).value));
	}
    });
    sumElem.textContent = sum.toFixed(2);
}

function buyCart() {

    cartData.forEach(function(val) {
	console.log(val);
	var counter = parseInt(document.getElementById('cartCounter' + val.snack_id).value);

	while (counter > 0) {
	    buyRequest(val.snack_id);
	    counter--;
	}


    });
    clearCart();
}

function clearCart() {
    document.getElementById('cartTableBody').textContent = "";
    cartData = new Array();
}

function addID() {
    searchIDRequest(document.getElementById('idField').value);
    calcCartPrice();
}


function fillFindDataList() {

    var xhr = syncGet(url + "finddatalist");

    var response = JSON.parse(xhr.response);

    checkStatus(response);

    var list = document.getElementById('findDataList');
    list.innerHTML = "";


    response.list.forEach(function(val) {

	var option = document.createElement('option');
	option.setAttribute('value', val.snack_name);
	list.appendChild(option);

    });


}

fillFindDataList();
