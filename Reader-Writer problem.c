#include<omp.h>
    #include<semaphore.h>
    #include<stdio.h>
    #include<unistd.h>

    int var=10;
    int ReadCount=0;

    sem_t Sem;

    int main()
    {
        sem_init(&Sem, 0, 1);
        int ThreadId = 0;
        int NReader, NWriter;
        int i,j;

        printf("\nEnter number of readers: ");
        scanf("%d",&NReader);
        printf("\nEnter number of writers: ");
        scanf("%d",&NWriter);

        #pragma omp parallel num_threads( (NReader+NWriter) )   shared(ThreadId)

        {
            printf("\n in parallel construct");



            #pragma omp for nowait
            for(i=0 ; i<NReader ; i++)
            {
                printf("\nReader started %d",i);
                //sleep(5);

                #pragma omp critical
                {
                    ReadCount++;
                    if(ReadCount==1)
                        sem_wait(&Sem);
                }

                ThreadId = omp_get_thread_num();
                printf("\n\nReader %d with thread id %d is reading shared variable %d ",i,ThreadId,var);

                #pragma omp critical
                 {
                    ReadCount--;
                    if(ReadCount==0)
                        sem_post(&Sem);
                }
            }
            #pragma omp for nowait
            for(j=0 ; j<NWriter ; j++)
            {
                printf("\nWriter started %d",j);
                sem_wait(&Sem);
                sleep(1);

                var=var+2;

                ThreadId = omp_get_thread_num();

                printf("\nWriter %d with ThreadId %d has updated the shared variable to %d ",j,ThreadId,var);

                sem_post(&Sem);
            }
             }
return 0;
    }
