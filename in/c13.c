char dog(){
    return "wofwof";
}

char cat(){
    return "miaw";
}

char cow(){
    return "muuu"; 
}

int main() {
    char animal[20] = "lion";
    char text[20];
    if(animal == "dog"){
        text = dog();
    }
    
    if(animal == "cat"){
        text = cat();
    }
    
    if(animal == "cow") {
        text = cow();
    }

    return 0;
}