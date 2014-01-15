var url = "db.php?";

/**
 * search on database and inputs this in the table
 */
function searchRequest() {

    

    var search = document.getElementById('findString').value;

    var request = syncGet(url + "find=" + search);

    var response = JSON.parse(request.response, true);

    var tbody = document.getElementById('tableBody');
    tbody.innerHTML = "";

    response.find.forEach(function(data) {
	var item = document.createElement('tr');

	var idItem = document.createElement('td');
	idItem.textContent = data.snack_id;
	item.appendChild(idItem);

	var nameItem = document.createElement('td');
	nameItem.textContent = data.snack_name;
	item.appendChild(nameItem);

	var priceItem = document.createElement('td');
	priceItem.textContent = data.snack_price;
	item.appendChild(priceItem);
	console.log(idItem);
	tbody.appendChild(item);
    })
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
function buyRequest() {

    var buy = document.getElementById('buyField').value;

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
    for (i = 0; i < response['status'].length; i++) {

	var row = buildDataRow(response['data'][i]);

	var userItem = document.createElement('td');
	userItem.textContent = response['user'];
	row.appendChild(userItem);


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