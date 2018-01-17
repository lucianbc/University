console.log("Works");

var data = {
  n: null,
  board: null,
  celDim: null,
  colors: ['red', 'blue']
}

function randomInt(min, max) {
  return Math.floor(Math.random() * (max - min + 1)) + min;
}

function loadCells(n) {
  var dim = Math.floor((700 - 4) / n - 4);
  data.celDim = dim;
  for (let i = 0; i < n; i++) {
    for (let j = 0; j < n; j++) {
      var cel = document.createElement('div');
      cel.className = 'patrat';
      cel.style.width = dim + "px";
      cel.style.height = dim + "px";
      cel.setAttribute('data-linie', i);
      cel.setAttribute('data-coloana', j);
      cel.onmouseenter = function(event) {
        event.srcElement.style.border = '2px solid red';
      };
      cel.onmouseleave = function(event) {
        event.srcElement.style.border = '2px solid black';
        document.getElementById('tabla').style.border = '1px solid black';
      }
      cel.onmouseover = function(event) {
        event.stopPropagation();
        document.getElementById('tabla').style.border = '';
      }

      document.getElementById('tabla').appendChild(cel);
    }
  }
}

function generatePiece(team) {
  var l = randomInt(0, data.n - 1);
  var c = randomInt(0, data.n - 1);
  while (data.board[l][c] != 0) {
    l = randomInt(0, data.n - 1);
    c = randomInt(0, data.n - 1);
  }
  data.board[l][c] = team;
  var piece = document.createElement('div');
  piece.style.position = 'relative';
  piece.style.width = data.celDim / 2 + 'px';
  piece.style.height = data.celDim / 2 + 'px';
  piece.style.background = data.colors[team - 1];
  piece.style.borderRadius = '100%';

  piece.ondblclick = function(event) {
    event.preventDefault();
    event.srcElement.style.border = '2px dashed black';
    data.shouldMove = true;
    if (data.selectedPiece) {
      data.selectedPiece.style.border = '';
    }
    data.selectedPiece = event.srcElement;
    data.lastKey = undefined;
    data.selectedCell = {
      l: parseInt(event.srcElement.parentElement.dataset.linie),
      c: parseInt(event.srcElement.parentElement.dataset.coloana)
    }
  }

  document.querySelector("div[data-linie = '" + l.toString() + "'][data-coloana = '" + c.toString() + "']").appendChild(piece);
  console.log(l, c);
}

function getCell(l, c) {
  return document.querySelector("div[data-linie = '" + l.toString() + "'][data-coloana = '" + c.toString() + "']");
}

document.onkeydown = function(event) {
  console.log(event.keyCode);
  if (data.shouldMove && (data.lastKey == undefined || data.lastKey == event.keyCode)) {
    data.lastKey = event.keyCode;
    if (event.keyCode == 38) { // up
      if (data.selectedCell.l - 1 >= 0 &&
        data.board[data.selectedCell.l - 1][data.selectedCell.c] == 0) {
          data.board[data.selectedCell.l - 1][data.selectedCell.c] = data.board[data.selectedCell.l][data.selectedCell.c];
          data.board[data.selectedCell.l][data.selectedCell.c] = 0;
          data.selectedCell.l -= 1;
        }
    } else if (event.keyCode == 40) { // down
      if (data.selectedCell.l + 1 < data.n &&
        data.board[data.selectedCell.l + 1][data.selectedCell.c] == 0) {
          data.board[data.selectedCell.l + 1][data.selectedCell.c] = data.board[data.selectedCell.l][data.selectedCell.c];
          data.board[data.selectedCell.l][data.selectedCell.c] = 0;
          data.selectedCell.l += 1;
      }
    } else if (event.keyCode == 37) { // left
      if (data.selectedCell.c - 1 >= 0 &&
          data.board[data.selectedCell.l][data.selectedCell.c - 1] == 0) {
        data.board[data.selectedCell.l][data.selectedCell.c - 1] = data.board[data.selectedCell.l][data.selectedCell.c];
        data.board[data.selectedCell.l][data.selectedCell.c] = 0;
        data.selectedCell.c -= 1;
      }
    } else if (event.keyCode == 39) { //right
      if (data.selectedCell.c + 1 < data.n &&
          data.board[data.selectedCell.l][data.selectedCell.c + 1] == 0) {
        data.board[data.selectedCell.l][data.selectedCell.c + 1] = data.board[data.selectedCell.l][data.selectedCell.c];
        data.board[data.selectedCell.l][data.selectedCell.c] = 0;
        data.selectedCell.c += 1;
      }
    }
    getCell(data.selectedCell.l, data.selectedCell.c).appendChild(data.selectedPiece);
  }
}

window.onload = function() {
  console.log("loaded");
  document.getElementById('creeaza_tabla').addEventListener('click', function() {
    var range = document.getElementById('dimensiune');
    var dim = range.value;
    loadCells(parseInt(dim));
    data.n = parseInt(dim);
    data.board = [];
    for (var x = 0; x < data.n; x++) {
      data.board[x] = [];
      for (var y = 0; y < data.n; y++) {
        data.board[x][y] = 0;
      }
    }
    console.log(data.board);
    range.style.visibility = 'hidden';
    document.getElementById('creeaza_tabla').style.visibility = 'hidden';

    for (var i = 0; i < 2; i++) {
      generatePiece(1);
    }

    for (var i = 0; i < 2; i++) {
      generatePiece(2);
    }
  });

  document.getElementById('tabla').onmouseleave = function(event) {
    document.getElementById('tabla').style.border = '';
  }

  document.getElementById('tabla').onmouseenter = function (event) {
    document.getElementById('tabla').style.border = '1px solid black';
  }
}
