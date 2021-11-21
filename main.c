#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/***********************************/
/********* Zwischentest 2 *********/
/*********************************/
/*********PRIORITY QUEUE*********/
/*******************************/


enum priority
{
    //je niedriger der Wert desto höher die Priorität
    // dummie = leerer eintrag in queue

    dummie,
    lowest,
    lower,
    normal,
    high,
    highest

};

struct entry
{
    enum priority prty;
    char   message[32];
};



struct pqueue
{
    struct entry entries[10];
};

//Funktionssignatur -> siehe unten
int queueLen(struct pqueue* pqueue);

int isEmpty(struct pqueue* pqueue)
{
    if(queueLen(pqueue) == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }

    /*Alternative ohne queueLen()
    if(pqueue->entries[0].prty == dummie)
    {
        return 1;
    }else
    {
        return 0;
    }
    */

}



int isFull(struct pqueue* pqueue)
{
    //Implementierung mit queueLen()

    if(queueLen(pqueue) == 10)
    {
        return 1;
    }
    else
    {
        return 0;
    }



    /*Alternative ohne queueLen()

    for(int i = 0; i < 10; ++i)
    {
        if(pqueue->entries[i].prty == dummie)
        {
            return 0;
        }

    }

    return 1;

    */
}

int queueLen(struct pqueue* pqueue)
{

    int length;
    // For-Schleife ohne Körper zählt Einträge
    for(length = 0; length < 10 && pqueue->entries[length].prty != dummie; ++length);

    return length;
}


// Funktion für passende Schreibweise zur Anzahl der Elemente in der Queue
void printQueueLen(struct pqueue* pqueue)
{

    if(queueLen(pqueue) == 1)
    {
        printf("\npriority queue now contains %d entry", queueLen( pqueue ) );
    }
    else
    {
        printf("\npriority queue now contains %d entries", queueLen(pqueue) );
    }

}

char priorityToChar(enum priority priority)
{
    switch(priority)
    {
        case lowest:  return 'L';  break;
        case lower:   return 'l';  break;
        case normal:  return 'n';  break;
        case high:    return 'h';  break;
        case highest: return 'H';  break;
        default:      return '?';  break;
    }

}

void enqueue(struct pqueue* pqueue, struct entry entry)
{
    if(isFull(pqueue) == 1)
    {
        printf("\npriority queue already full!");
    }
    else
    {
        int pos;
        for(pos = 0;pqueue->entries[pos].prty >= entry.prty; ++pos);

        for(int i = 9;pos < i ;--i)
        {
            pqueue->entries[i] = pqueue->entries[i-1];
        }

        pqueue->entries[pos] = entry;

        printQueueLen(pqueue);
    }
}

void dequeue(struct pqueue* pqueue)
{
    if(isEmpty(pqueue) == 1)
    {
        printf("\npriority queue is empty!");
    }
    else
    {
        printf("\nMessage: %s",pqueue->entries[0].message);

        for(int i = 1; i < 10; ++i)
        {
            pqueue->entries[i-1] = pqueue->entries[i];
        }

        struct entry         placeholder;
        placeholder.prty =        dummie;
        pqueue->entries[9] = placeholder;

        printQueueLen(pqueue);

    }

}




void printQueue(struct pqueue* pqueue)
{

    if(isEmpty(pqueue)== 1)
    {
        printf("\nempty queue");
    }
    else
    {

        for(int i = 0; i < queueLen(pqueue);++i)
        {
            printf("\n%c: %s",priorityToChar(pqueue->entries[i].prty) ,pqueue->entries[i].message);
        }
    }


}




// action?
char getMenu()
{
    char input;
    printf("\nChoose action: print queue (p), enqueue entry (e), dequeue entry (d) or exit (x): ");
    scanf(" %c", &input);

    while(input != 'p' && input != 'e' && input != 'd' && input != 'x')
    {

        printf("\nInput invalid! Try again: ");
        scanf(" %c", &input);

    }

    return input;

}

enum priority charToPriority(char priority)
{
    switch(priority)
    {
        case 'L': return lowest;  break;
        case 'l': return lower;   break;
        case 'n': return normal;  break;
        case 'h': return high;    break;
        case 'H': return highest; break;
        default:  return '?';     break;
    }

}


struct entry getNewEntry()
{

    char input;
    printf("\nChoose priority: lowest (L), low (l), normal (n), high (h), highest (H): ");
    scanf(" %c", &input);

    while(input != 'L' && input != 'l' && input != 'n' && input != 'h' && input != 'H')
    {

        printf("\nInput invalid! Try again: ");
        scanf(" %c", &input);

    }

    char msg[32];
    printf("\nChoose message: ");
    scanf("%32s", &msg[0]);

    struct entry startEntry;
    strcpy(startEntry.message, msg);
    startEntry.prty = charToPriority(input);


    return startEntry;

};


int main()
{
    //Initialisierung mit Random-Wert 'q'
    char rValue= 'q';

    struct pqueue myQueue;
    myQueue.entries[0].prty = dummie; //Initialisierung der Queue als leer;
    struct entry myEntry;

    while(rValue != 'x')
    {
        rValue = getMenu();

        switch(rValue)
        {
            case'p':
                printQueue(&myQueue);
                break;

            case'e':
                myEntry = getNewEntry();
                enqueue(&myQueue, myEntry);

                break;

            case'd':
                dequeue(&myQueue);
                break;

                //While-Schleife beendet Programm
            case'x':
                //Nothing to do here
                break;

        }

    }

    return 0;
}


//Übriggebliebene Main aus der Testphase

/*
int main()
{





    printf("\nMessage: %s", eintrag1.message);
    printf("\nPrio: %d", eintrag1.prio);

    // char input;
    //scannen? scanf(" %c", &getMenu(input)); ????
   char input;
   scanf(" %c", getMenu(input));


    struct entry message1;
    strcpy(message1.message, "Hello");
    message1.prty = normal;

    struct entry message2;
    strcpy(message2.message, "Griaß di");
    message2.prty = high;

    struct entry placeholder;
    strcpy(placeholder.message, "Test");
    placeholder.prty = dummie;

    struct pqueue pq1;
    pq1.entries[0] = message1;
    pq1.entries[1] = message1;
    pq1.entries[2] = message1;
    pq1.entries[3] = message1;
    pq1.entries[4] = message1;
    pq1.entries[5] = message1;
    pq1.entries[6] = message1;
    pq1.entries[7] = message1;
    pq1.entries[8] = message1;
    pq1.entries[9] = message2;

    getMenu();
    dequeue(&pq1);
   enqueue(&pq1, message2);

   printQueue(&pq1);

   printf("\nAusgabe: %d", isEmpty(&pq1));
   printf("\nLaenge: %d", queueLen(&pq1));


    return 0;
}
*/
