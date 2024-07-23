

// clicker.addEventListener("click", function () { 
//     var sub = document.getElementById("sub");
//     console.log("Click");
//     sub.innerHTML = "WASP";

// });

var number = 0;
function clicked() { 
    console.log("CLICKED!");
    var sub = document.getElementById("sub");
    sub.innerText = number++;
};