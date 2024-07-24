void Billinfo(struct list f[], char name,  char date [20])
{
    int change;
    int received;
    int size;
    int total = 0;
    printf ("\t    Manhattan Kitchen\n");
    printf ("\t    -------------------\n");
    printf ("Date: %c\n", date);
    printf ("Customer Name: %c\n", name);
    printf ("\n");
    printf ("--------------------------------------\n");
    for (int i = 0; i < size; i++)
    printf ("\n");
    
    printf ("\t\tTotal: %d\n", total);
    
    printf ("Enter the amount received: ₹");
    scanf("%d", &received);
    
    change = received - total;

    printf ("Change to be given: ₹%d\n", change);
    printf("\n");
    printf ("--------------------------------------\n");
    printf ("\t Thank You for your Visiting. \n");
    printf ("\t Visit soon. \n"); 
}