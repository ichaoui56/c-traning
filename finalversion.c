#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<time.h>

typedef struct tache
    {
        int ID;
        char titre[100];
        char description[100];
        char statut[100];
        struct tm deadline;
    }tache;

  //fonction de saisi d'une seule tache :

int une_seule_tache(tache info[], int n) {

    printf("\n                            La %d tache : \n",n + 1 );

    info[n].ID = n + 1;
    printf("\n                         ID de la tache est %d \n", info[n].ID);

    printf("\n                        Entrer titre de tache : ");
    scanf(" %[^\n]", info[n].titre);

    printf("\n                        Entrer description de tache : ");
    scanf(" %[^\n]", info[n].description);

    printf("\n                        Enter the deadline (YYYY-MM-DD): ");
    scanf("%d-%d-%d", &info[n].deadline.tm_year,&info[n].deadline.tm_mon,&info[n].deadline.tm_mday);
    info[n].deadline.tm_year -= 1900;
    info[n].deadline.tm_mon -= 1;

    printf("\n                        Entrer un statut de tache (todo , doing , done ): ");
    scanf("%s", info[n].statut);

    while (1) {
        if (strcmp(info[n].statut, "todo") == 0 || strcmp(info[n].statut, "doing") == 0 || strcmp(info[n].statut, "done") == 0)
            break;
        else {
            printf("\n                        Invalid statut.\n");
            printf("\n                        Entrer 'todo', 'doing', or 'done': ");
            scanf("%s", info[n].statut);
        }
    }

    printf("\n                        Tache ajoutée avec succès.\n");

    return n+1;
}

//fonction de saisi plusieurs taches :

int plusieurs_tache(tache info[], int n) {
    int Size;
    printf("\n                        Enter le nombre des taches :  ");
    scanf("%d", &Size);

    for (int i = 0; i < Size; i++) {
        n = une_seule_tache(info, n);
    }
  return n;
}

// Affichage des taches :

void affichage(int n, tache info[]) {

    char date_str[20];

    for (int i = 0; i < n; i++) {
        printf("\n                      *************La %d tache*************\n", info[i].ID);
        printf("\n                        l'identifiant de la tache est %d .\n", info[i].ID);
        printf("\n                        le titre de la tache est %s .\n", info[i].titre);
        printf("\n                        le description de la tache est %s .\n", info[i].description);
        strftime(date_str, 20 , "%Y-%m-%d", &info[i].deadline);
        printf("\n                        la date limite (deadline) de la tache est %s .\n", date_str);

        printf("\n                        la statut de la tache est %s .\n", info[i].statut);
    }
}

// fonction de temps :

    int difference_days(tache t){
        time_t now;
        time(&now);

        double difference = difftime(mktime(&t.deadline),now);
        double hours_difference = difference / 3600.0;
        int jour_diff=(int)hours_difference/24;
    return jour_diff;
   }




//Afficher la liste des tâches dont le deadline 3 jours ou moins  :

void afficher_under_3_days(tache info[], int n) {

    char date_str[20];

    for (int i = 0; i < n; i++) {
        if (difference_days(info[i]) <= 3) {
            printf("\n                      *************La %d tache*************\n", info[i].ID);
            printf("\n                        l'identifiant de la tache est %d.\n", info[i].ID);
            printf("\n                        le titre de la tache est %s.\n", info[i].titre);
            printf("\n                        la description de la tache est %s.\n", info[i].description);
            strftime(date_str, 20 , "%Y-%m-%d", &info[i].deadline);
            printf("\n                        la date limite (deadline) de la tache est %s.\n", date_str);

            printf("\n                        la statut de la tache est %s.\n", info[i].statut);
        }
    }
}
// sortAlpha :

void sortAlpha(tache info[],int n){

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (strcmp(info[i].titre, info[j].titre) > 0) {
                tache swap = info[i];
                info[i] = info[j];
                info[j] = swap;
            }
        }
    }


}

// Comparer deux deadline :

int compare_tm(struct tm deadline1, struct tm deadline2) {
    // Convert struct tm to time_t
    time_t time1 = mktime(&deadline1);
    time_t time2 = mktime(&deadline2);

    // Compare time_t values
    if (time1 > time2) {
        return 1; 
    }else {
        return -1; 
    }
}

// sortdeadline :

void sortDeadline(tache info[],int n){

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if(compare_tm(info[i].deadline,info[j].deadline)>0){
                tache swap = info[i];
                info[i] = info[j];
                info[j] = swap;
            }
        }
    }


}


// Modifier la titre d'une tâche par son ID :

void modifier_titre(tache info[], int n) {
    int id;
    printf("\n                           Entrer l'ID de la tache à modifier : ");
    scanf("%d", &id);
    for (int i = 0; i < n; i++) {
        if (info[i].ID == id) {
            printf("\n        -------------------Entrer la nouvelle titre de la tache-------------------------\n\n\t\t\t\t\t");
            scanf(" %[^\n]", info[i].titre);
            printf("\n                             Titre mise à jour avec succès.\n");
            return;
        }
    }
    printf("\n                            Aucune tache trouvée avec cet ID.\n");
}

// Modifier la description d'une tâche par son ID :

void modifier_description(tache info[], int n) {
    int id;
    printf("\n                             Entrer l'ID de la tache à modifier : ");
    scanf("%d", &id);
    for (int i = 0; i < n; i++) {
        if (info[i].ID == id) {
            printf("\n       -------------------Entrer la nouvelle description de la tache-------------------\n\n\t\t\t\t\t");
            scanf("                        %[^\n]", info[i].description);
            printf("\n                             Description mise à jour avec succès.\n");
            return;
        }
    }
    printf("\n                           Aucune tache trouvée avec cet ID.\n");
}



// Modifer la statut d'une tâche par son ID :

void modifier_statut(tache info[], int n) {
    int id;
    printf("\n                         Entrer l'ID de la tache à modifier : ");
    scanf("%d", &id);
    for (int i = 0; i < n; i++) {
        if (info[i].ID == id) {
            printf("\n                        Entrer un statut de tache (todo , doing , done ): ");
            scanf("%s", info[n].statut);
            while (1) {
                if (strcmp(info[n].statut, "todo") == 0 || strcmp(info[n].statut, "doing") == 0 || strcmp(info[n].statut, "done") == 0)
            break;
                else {
            printf("\n                        Invalid statut.\n");
            printf("\n                        Entrer 'todo', 'doing', or 'done': ");
            scanf("%s", info[n].statut);
                }
            }
        }

            return;
        
        
    printf("\n                           Aucune tache trouvée avec cet ID.\n");
        }
}



// Modifer la deadline d'une tâche par son ID :

void modifier_deadline(tache info[], int n) {
    int id;
    printf("\n                         Entrer l'ID de la tache à modifier : ");
    scanf("%d", &id);

    for (int i = 0; i < n; i++) {
        if (info[i].ID == id) {
            printf("\n       -------------------Entrer la nouvelle deadline de la tache------------------------\n\n\t\t\t\t\t");
            scanf(" %d-%d-%d", &info[i].deadline.tm_year, &info[i].deadline.tm_mon, &info[i].deadline.tm_mday);
            info[i].deadline.tm_year -= 1900;
            info[i].deadline.tm_mon -= 1;

            printf("\n                             Deadline mise à jour avec succès.\n");
            return;
        }
    }
    printf("\n                         Aucune tache trouvée avec cet ID.\n");
}

// Modifer la tache :

void modifer_tache(tache info[],int n) {
    int id;
    printf("\n                         Entrer l'ID de la tache à modifier : ");
    scanf("%d",&id);
    for(int i = 0;i < n; i++){
        if(info[i].ID==id){
            printf("\n       -------------------Entrer la nouvelle titre de la tache-------------------------\n\n\t\t\t\t\t");
            scanf("                           %[^\n]",info[i].titre);

            printf("\n       -------------------Entrer la nouvelle description de la tache-------------------\n\n\t\t\t\t\t");
            scanf("                         %[^\n]",info[i].description);

            printf("\n       -------------------Entrer la nouvelle deadline (YYYY-MM-DD)---------------------\n\n\t\t\t\t\t ");
            scanf(" %d-%d-%d", &info[i].deadline.tm_year, &info[i].deadline.tm_mon, &info[i].deadline.tm_mday);
            info[i].deadline.tm_year -= 1900;
            info[i].deadline.tm_mon -= 1;

            printf("\n                        Entrer un statut de tache (todo , doing , done ): ");
            scanf("%s", info[n].statut);
            while (1) {
                if (strcmp(info[n].statut, "todo") == 0 || strcmp(info[n].statut, "doing") == 0 || strcmp(info[n].statut, "done") == 0)
                break;
                else {
                    printf("\n                        Invalid statut.\n");
                    printf("\n                        Entrer 'todo', 'doing', or 'done': ");
                    scanf("%s", info[n].statut);

                }
            }
            printf("\n                             tache mise à jour avec succès.\n");
            return;

            }
        }
    printf("\n                             Aucune tache trouvée avec cet ID.\n");
}

// Supprimer une tâche par son ID :

int supprimer_tache(tache info[], int n) {
    int id;
    printf("\n                         Entrer l'ID de la tache à supprimer : ");
    scanf("%d", &id);

    int pos = -1;

    for (int i = 0; i < n; i++) {
        if (info[i].ID == id) {
            pos = i;

        }
    }

    if (pos != -1) {
        for (int i = pos; i < n - 1; i++) {
            info[i] = info[i + 1];
        }
        printf("\n                         Tache avec l'ID %d supprimée avec succès.\n", id);
        return n - 1;

    }
    printf("\n                         Aucune tache trouvée avec l'ID %d.\n", id);
    return n;

}

// recherche par identifiant :

void rechercher_identifiant(tache info[], int n) {
    int id;
    char date_str[20];
    printf("\n                         Entrer l'identifiant à rechercher : ");
    scanf(" %d", &id);

    for (int i = 0; i < n; i++) {
        printf("\n                         Comparaison avec ID %d. \n", info[i].ID);
        if (info[i].ID == id) {
            printf("\n                      ********La tache trouvée : ********\n");
            printf("\n                        l'identifiant de la tache est %d .\n", info[i].ID);
            printf("\n                        le titre de la tache est %s .\n", info[i].titre);
            printf("\n                        le description de la tache est %s .\n", info[i].description);
            strftime(date_str, 20 , "%Y-%m-%d", &info[i].deadline);
            printf("\n                        la date limite (deadline) de la tache est %s .\n", date_str);
            printf("\n                        la statut de la tache est %s .\n", info[i].statut);
            printf("\n\n");
            return;
        }
    }
    printf("\n                             Aucune tache trouvée avec l'identifiant '%d'.\n", id);
}

// recherche par titre :

int rechercher_titre(tache info[], int n) {
    char trouver_titre[100], date_str[20];

    printf("\n                         Entrer le titre à rechercher : ");
    scanf(" %[^\n]", trouver_titre);

    for (int i = 0; i < n; i++) {
        printf("\n                         Comparaison avec le titre %s. \n", info[i].titre);
        if (strcmp(info[i].titre, trouver_titre) == 0) {
            printf("\n                     ********La tache trouvée : ********\n");
            printf("\n                        l'identifiant de la tache est %d .\n", info[i].ID);
            printf("\n                        le titre de la tache est %s .\n", info[i].titre);
            printf("\n                        le description de la tache est %s .\n", info[i].description);
            strftime(date_str, 20 , "%Y-%m-%d", &info[i].deadline);
            printf("\n                        la date limite (deadline) de la tache est %s .\n", date_str);
            printf("\n                        la statut de la tache est %s .\n", info[i].statut);
            return i;
        }
    }

    printf("\n                         Aucune tache trouvée avec le titre '%s'.\n", trouver_titre);

    return -1;
}

// statistique :

    // Afficher le nombre de tâches complètes et incomplètes :

    void complt_incomplt(tache info[] , int n ) {

        int taches_completes =0;
        int taches_incompletes =0;

        for (int i = 0; i < n; i++) {
            if (strcmp(info[i].statut, "done") == 0) {
            taches_completes++;
            } else {
            taches_incompletes++;
            }
        }
        printf("Number of tasks completed : %d\n", taches_completes);
        printf("Number of tasks incompleted : %d\n", taches_incompletes);
}

// Afficher le nombre de jours restants jusqu'au délai de chaque tâche :

    void affichage_jusque_delai(tache info[],int n){
        int i;
        for(i=0;i<n;i++){
            printf("\nle nombre de jours restant au delai de cette tache %d est : %d",info[i].ID,difference_days(info[i]));
        }
}


int main(){

    int n = 0 , choix ;
    char choix2 , choix3 , choix4 , choix5 ;

    tache info[100];

    do {
    printf("\n\n");
    printf("**======================|(    📃   Menu   📃    )|=======================**\n");
    printf("||                                                                       ||\n");
    printf("||                       1.Pour ajouter une tache.                       ||\n");
    printf("||                       2.Pour ajouter plusieurs tache.                 ||\n");
    printf("||                       3.Pour afficher les tache.                      ||\n");
    printf("||                       4.Pour modifier une tache.                      ||\n");
    printf("||                       5.Pour supprimer une tache.                     ||\n");
    printf("||                       6.Pour rechrcher une tache.                     ||\n");
    printf("||                       7.Pour afficher les statistiques.               ||\n");
    printf("||                            0.Pour quitter.                            ||\n");
    printf("||                                                                       ||\n");
    printf("**=======================================================================**\n");
    printf("\n                            Enter le choix : ");
    scanf("%d",&choix);
    printf("\n\n");

        switch(choix){

            case 1 :

                n = une_seule_tache(info,n);
                break;

            case 2 :

                n = plusieurs_tache(info,n);
                break;

            case 3 :

                printf("\n\n");
                printf("**=========================|(   📺    AFFICHAGE    📺    )|========================** \n");
                printf("||                                                                                  ||\n");
                printf("||                       a.Pour afficher par order alphabetique.                    ||\n");
                printf("||                           b.Pour afficher par deadline.                          ||\n");
                printf("||             c.Pour afficher dont le deadline est dans 3 jours ou moins.          ||\n");
                printf("||                                                                                  ||\n");
                printf("**==================================================================================**\n");
                printf("\n                                Enter le choix : ");
                scanf(" %c",&choix2);
                printf("\n\n");

                    switch(choix2){

                        case 'a' :

                            sortAlpha(info,n);
                            affichage(n,info);
                            break;

                        case 'b' :

                            sortDeadline(info,n);
                            affichage(n,info);
                            break;

                        case 'c' :

                            afficher_under_3_days(info,n);
                            break;
                    }

                break;

            case 4 :

                printf("\n\n");
                printf("**=========================|(    🛠️   MODIFICATION   🛠️  )|===============  ==========** \n");
                printf("||                                                                                   ||\n");
                printf("||                         a.Pour modifier le titre de tache.                        ||\n");
                printf("||                      b.Pour modifier la description de tache.                     ||\n");
                printf("||                           c.Pour modifer le deadline.                             ||\n");
                printf("||                            d.Pour modifier le statut.                             ||\n");
                printf("||                          e.Pour modifier tous la tache.                           ||\n");
                printf("||                                                                                   ||\n");
                printf("**===================================================================================**\n");
                printf("\n                                Enter le choix : ");
                scanf(" %c",&choix3);
                printf("\n\n");

                    switch(choix3){

                        case 'a' :

                            modifier_titre(info,n);
                            break;

                        case 'b' :

                            modifier_description(info,n);
                            break;

                        case 'c' :

                            modifier_deadline(info,n);
                            break;

                        case 'd' :

                            modifier_statut(info,n);
                            break;

                        case 'e' :

                            modifer_tache(info,n);
                            break;

                        default:

                            printf("\n                       Choix incorrect.\n");
                            break;
                    }
                break;

            case 5 :

                n = supprimer_tache(info,n);
                break;

            case 6 :

                printf("\n\n");
                printf("**========================|(  🔎    RECHERCHER    ��    )|==========================**\n");
                printf("||                                                                                  ||\n");
                printf("||                        a.Pour chercher par identifiant.                          ||\n");
                printf("||                          b.Pour rechercher par titre.                            ||\n");
                printf("||                                                                                  ||\n");
                printf("**==================================================================================**\n");
                printf("\n                               Enter le choix : ");
                scanf(" %c",&choix4);
                printf("\n\n");

                    switch(choix4){

                        case 'a' :

                             rechercher_identifiant(info,n);
                            break;

                        case 'b' :

                             rechercher_titre(info,n);
                            break;

                        default:

                            printf("\n                              Choix incorrect.\n");
                            break;
                    }

                break;

            case 7 :

                printf("\n\n");
                printf("**=========================|(   📺    STATISTIQUE    📺    )|========================** \n");
                printf("||                                                                                    ||\n");
                printf("||                       a.Afficher le nombre total des tâches.                       ||\n");
                printf("||               b.Afficher le nombre de tâches complètes et incomplètes.             ||\n");
                printf("||          c.Afficher le nombre de jours restants jusqu'au délai de chaque tâche.    ||\n");
                printf("||                                                                                    ||\n");
                printf("**====================================================================================**\n");
                printf("\n                                Enter le choix : ");
                scanf(" %c",&choix5);
                printf("\n\n");

                    switch(choix5){

                        case 'a' :

                            printf("\n                            Le nombre total des tâches.  : %d\n", n);
                            break;

                        case 'b' :

                            complt_incomplt(info,n);
                            break;

                        case 'c' :

                            affichage_jusque_delai(info,n);
                            break;
                    }

                break;

            case 0 :

                printf("\n                           *** до свидания ***                              \n");
                exit(0);
                break;

            default:
                printf("\n                              Choix incorrect .");
                break;
        }
    } while (choix != 0);

    return 0;
}

