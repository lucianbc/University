window.onload = function () {
  console.log("loaded!");
}

function creeazaImagineDupa(elem){
	//creez un element de tip imagine (tagul img)
	var imag=document.createElement("img");

	//ii setez sursa
	imag.src="http://irinaciocan.ro/imagini/nenea_html.png";

	//o adaug in pagina , intr-un element parinte - in cazul de fata body (abia acum e vizibila)
	elem.parentNode.appendChild(imag);
}

function creeazaImagineInainte(elem){
	//creez un element de tip imagine (tagul img)
	var imag=document.createElement("img");

	//ii setez sursa
	imag.src="http://irinaciocan.ro/imagini/nenea_html.png";

	//o adaug in pagina , intr-un element parinte - in cazul de fata body, inainte de elem
	elem.parentNode.insertBefore(imag,elem.parentNode.firstChild);
}

function stergePrimaImagine(elem){
	//creez un element de tip imagine (tagul img)
	var imag=document.getElementsByTagName("img")[0];

	//ii setez sursa
	imag.src="http://irinaciocan.ro/imagini/nenea_html.png";

	//o adaug in pagina , intr-un element parinte - in cazul de fata body (abia acum e vizibila)
	imag.parentNode.removeChild(imag);
}

function goLeft(elem) {
  var leftEl = elem.previousSibling;
  if (leftEl == null) return;
  var parent = elem.parentNode;
  var newButton = elem.cloneNode(true);
  var newLeftEl = leftEl.cloneNode(true);

  parent.replaceChild(newButton, leftEl);
  parent.replaceChild(newLeftEl, elem);
}

function swap(e1, e2) {
  var parent = e1.parentNode;
  var newE1 = e1.cloneNode(true);
  var newE2 = e2.cloneNode(true);

  parent.replaceChild(e1, newE2);
  parent.replaceChild(e2, newE1);
}

function goRight(elem) {
  var rightEl = elem.nextSibling;
  if (rightEl == null) return;

  var parent = elem.parentNode;
  var newButton = elem.cloneNode(true);
  var newRightEl = rightEl.cloneNode(true);

  parent.replaceChild(newButton, rightEl);
  parent.replaceChild(rightEl, elem);
}
