int main(){

    //exercício 1
    int nums[] = { 30, 17, 3, 4, 5, 6, 7, 8, 9, 10 };
    int* ptr = nums;
    char* ptr2 = (char*) ptr; //será avisado de warning se não forçar o tipo
    int i, bytes;
    // o for começa a ir até 40 para ter 4 vezes cada elemento
    int total = 10 * sizeof(int);
    for(i=0, bytes=0; i < total; i++, bytes+=1)
        printf("%d: %p + %d bytes = %p ==> %d\n",
            i, ptr2, bytes, (ptr2+i), *(ptr2+i));
    return 0;

}
