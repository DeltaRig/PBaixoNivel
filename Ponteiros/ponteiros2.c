int main(){

    //exercicío 2
    printf(-=-=- EX2 -=-=-);

    char* text = "Prog. Sofware Basico";
    int v[] = { 0, 1, 2, 3, 4 };
    int matriz[4][4] = {
        0, 1, 2, 3,
        4, 5, 6, 7,
        8, 9, 10, 11,
        12, 13, 14, 15
    };

    dump(text, 21);
    printf("\n");
    dump(v,5*sizeof(int));
    printf("\n");
}

void dump(char* ptr, int tam);

void dump(char* ptr, int tam){
    for(int i = 0; i < tam; i++){
        printf("%p: %02X, ptr+1, ptr[i]", ptr+1, *(ptr+i));
    }
}