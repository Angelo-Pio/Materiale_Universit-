function storeUser() {

    var form = document.userForm;
    var val = true;
    var message = "";
    // Checks
    if (form.nome.value == "") { val = false; message = "Inserisci un nome\n"; }
    if (form.cognome.value == "") { val = false; message = message.concat("Inserisci un cognome\n"); }
    if (form.matricola.value == "") { val = false; message = message.concat("Inserisci una matricola\n"); }

    if (val == false) { alert(message); return false; }
    else{ message = "user stored correctly";}

    var user = {
        "name": form.nome.value,
        "surname": form.cognome.value,
        "matricola": form.matricola.value
    };
    user = JSON.stringify(user);
    var username = user.name;
    localStorage.setItem("user : ".concat(username), user);

    alert(message);
    return true;
}
function printUsers() {


    for (var i = 0; i < localStorage.length; i++) {

        var user = JSON.parse(localStorage.getItem(localStorage.key(i)));
        // buff.push(user);
        // alert(user.name);
        var tbody = document.getElementById("user_table");

        console.log(tbody.id);
        var row = tbody.insertRow();
        var NOME = row.insertCell(0);
        var CONGNOME = row.insertCell(1);
        var MATRICOLA = row.insertCell(2);



        NOME.innerHTML = user.name;
        CONGNOME.innerHTML = user.surname;
        MATRICOLA.innerHTML = user.matricola;
    }

}

function clearStorage() {

    localStorage.clear();


}

function addEventHandlers(){

    var div = document.getElementsByTagName("div");
    for(i = 0; i < div.length; i++){

        console.log(div.name);
        div[i].addEventListener("mouseover",turnRed);
    }

    var classes = document.getElementsByClassName("c1");

    for(i = 0; i < classes.length ; i++){
        classes[i].addEventListener("click", turnBlue);
        classes[i].addEventListener("dblclick", disappear);

    }

    // var spanC2 = document.getElementsByTagName("span") ;
    
    // for(i = 0; i < spanC2.length ; i++){
    //     if(spanC2[i].className == "c2"){

    //         spanC2[i].addEventListener("click", turnGreen);
    //     }

    // }

    // Meglio 

    var span = document.querySelectorAll("span.c2");
    for (let index = 0; index < span.length; index++) {
        span[index].addEventListener("click",turnGreen);        
    }
    
}


function turnRed(e){

    if(e.target.style.color == "red"){
        
        e.target.style.color = "";
    }else{

        e.target.style.color = "red";
    }
}
function turnBlue(e){

        e.target.style.color = "blue";
}
function turnGreen(e){

        e.target.style.color = "green";
}
function disappear(e){

    e.target.style.visibility = "hidden";
    
}