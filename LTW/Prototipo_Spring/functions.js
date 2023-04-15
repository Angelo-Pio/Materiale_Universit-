function g(){
    
    window.title = "Hello"
    ;

    // window.open("http://www.google.com","Eccoti google allora");
}

function check(){


    var value1 = document.submission_form.male.checked ;
    var value2 = document.submission_form.female.checked ;
    if(value1 == true && value2 == true){
        window.alert("checked");
    }else{
        window.alert("unchecked");

    }


}