2)JOIN:
#include <iostream>
#include <unistd.h>
#include<ctime>
#include <pthread.h>
using namespace std;
string s;
time_t Time = time(0);
void* func(void*)
{
    s = ctime(&Time);
    sleep(1);
    cout << "Child thread Created " << s << endl;
}
int main()
{
    s = ctime(&Time);
    pthread_t t1[5];
    for(int i=0; i<5; i++)
    {
        cout << "Thread T[" << i << "] is Created " << s << endl;
        pthread_create(&t1[i], NULL, &func, NULL);
        pthread_join(t1[i], NULL);
}
exit(EXIT_SUCCESS);
return 0;
}


