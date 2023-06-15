/* programul calculeaza cu un algoritm dublu adaptativ integrala functiei
 * log(x)/sqrt(x) pe intervalul [0,1] (singularitate logaritmica
 * la limita inferioara)
 */

#include <stdio.h>
#include <math.h>
#include <gsl/gsl_integration.h>

// functia de integrat
double f (double x, void * params) 
{
    /* biblioteca GSL defineste pentru generalitate toate functiile
     * de lucru astfel incat sa accepte parametri externi, definiti
     * ca pointeri pe void; acestia trebuie redefiniti in corpul functiei
     * pentru a asigura functionalitatea dorita.
     * In cazul de fata, nu este nevoie de parametri
     * suplimentari, astfel ca valoarea alpha va fi initializata cu 1
     * la momentul apelului functiei.
     */
    double alpha = *(double *) params;
    double y = log(alpha*x) / sqrt(x);
    return y;
}

int main (void)
{
    // limitele intervalului de integrare
    double a = 0., b = 1.;
    // nr. evaluari functionale ale algoritmului gsl_integration_cquad
    size_t nevals;
    /*aloc spatiul RAM necesar dezvoltarii algoritmului - aici se aloca
     * suficient spatiu RAM pentru 1000 subintervale (valori double), valorile
     * integralelor si estimarilor de eroare corespunzatoare acestor subintervale
     */
    gsl_integration_cquad_workspace * w = gsl_integration_cquad_workspace_alloc (1000);
    
    // rezultatul si eroarea estimata
    double result, error;
    /* aici nu includ nici un parametru suplimentar, functia de integrat
     * este complet definita de valoarea argumentului x.
     */
    double alpha = 1.0;

    //definitia obiectului gsl_function necesar aplicarii algoritmului
    gsl_function F;
    F.function = &f;
    F.params = &alpha;

    /* integrarea adaptativa cu algoritmul CQUAD;
     * noile subintervale sunt concentrate in vecinatatea
     * singularitatii. Subintervalele si rezultatele corespunzatoare
     * sunt stocate in spatiul de lucru w, eroarea relativa asteptata 
     * fiind 1e-7
     */   
    gsl_integration_cquad (&F, a, b, 0, 1e-7, w, &result, &error, &nevals);
    printf ("rezultat = % .18f\n", result);
    printf ("eroare estimata = % .18f\n", error);
    printf ("intervale = %d\n", w->size);
    
    gsl_integration_cquad_workspace_free (w);
    return 0;
}
    
