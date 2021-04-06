int counter_open_totaal = 200;
int pointerday = 0;
int counter_week_totaal = 42;
int counter_maand_totaal = 200;

vector<int> counter_dagen_week = {25, 30, 29, 25, 33, 23, 35};
vector<int> counter_afgelopen_dagen = {0, 6, 8, 7, 5, 9, 7, 5, 10, 6, 7, 3, 8, 9, 6, 7, 5, 8, 10, 6, 6, 5, 8, 4, 11, 7, 6, 8, 9, 4};

cout << "Totaal is nu: " << counter_open_totaal << ", vandaag is nu: " << counter_afgelopen_dagen[0] << " deze week is nu: " << counter_week_totaal << " deze maand is nu: " << counter_maand_totaal << endl;
if (pointerday == 0)
    cout << "het is nu maandag, totaal op maandagen: " << counter_dagen_week[0] << ", totaal op dinsdagen: " << counter_dagen_week[1] << ", totaal op woensdagen: " << counter_dagen_week[2] << ", totaal op donderdagen: " << counter_dagen_week[3] << ", totaal op vrijdagen: " << counter_dagen_week[4] << ", totaal op zaterdagen: " << counter_dagen_week[5] << ", totaal op zondagen: " << counter_dagen_week[6] << endl;
if (pointerday == 1)
    cout << "het is nu dinsdag, totaal op maandagen: " << counter_dagen_week[0] << ", totaal op dinsdagen: " << counter_dagen_week[1] << ", totaal op woensdagen: " << counter_dagen_week[2] << ", totaal op donderdagen: " << counter_dagen_week[3] << ", totaal op vrijdagen: " << counter_dagen_week[4] << ", totaal op zaterdagen: " << counter_dagen_week[5] << ", totaal op zondagen: " << counter_dagen_week[6] << endl;
if (pointerday == 2)
    cout << "het is nu woensdag, totaal op maandagen: " << counter_dagen_week[0] << ", totaal op dinsdagen: " << counter_dagen_week[1] << ", totaal op woensdagen: " << counter_dagen_week[2] << ", totaal op donderdagen: " << counter_dagen_week[3] << ", totaal op vrijdagen: " << counter_dagen_week[4] << ", totaal op zaterdagen: " << counter_dagen_week[5] << ", totaal op zondagen: " << counter_dagen_week[6] << endl;
if (pointerday == 3)
    cout << "het is nu donderdag, totaal op maandagen: " << counter_dagen_week[0] << ", totaal op dinsdagen: " << counter_dagen_week[1] << ", totaal op woensdagen: " << counter_dagen_week[2] << ", totaal op donderdagen: " << counter_dagen_week[3] << ", totaal op vrijdagen: " << counter_dagen_week[4] << ", totaal op zaterdagen: " << counter_dagen_week[5] << ", totaal op zondagen: " << counter_dagen_week[6] << endl;
if (pointerday == 4)
    cout << "het is nu vrijdag, totaal op maandagen: " << counter_dagen_week[0] << ", totaal op dinsdagen: " << counter_dagen_week[1] << ", totaal op woensdagen: " << counter_dagen_week[2] << ", totaal op donderdagen: " << counter_dagen_week[3] << ", totaal op vrijdagen: " << counter_dagen_week[4] << ", totaal op zaterdagen: " << counter_dagen_week[5] << ", totaal op zondagen: " << counter_dagen_week[6] << endl;
if (pointerday == 5)
    cout << "het is nu zaterdag, totaal op maandagen: " << counter_dagen_week[0] << ", totaal op dinsdagen: " << counter_dagen_week[1] << ", totaal op woensdagen: " << counter_dagen_week[2] << ", totaal op donderdagen: " << counter_dagen_week[3] << ", totaal op vrijdagen: " << counter_dagen_week[4] << ", totaal op zaterdagen: " << counter_dagen_week[5] << ", totaal op zondagen: " << counter_dagen_week[6] << endl;
if (pointerday == 6)
    cout << "het is nu zondag, totaal op maandagen: " << counter_dagen_week[0] << ", totaal op dinsdagen: " << counter_dagen_week[1] << ", totaal op woensdagen: " << counter_dagen_week[2] << ", totaal op donderdagen: " << counter_dagen_week[3] << ", totaal op vrijdagen: " << counter_dagen_week[4] << ", totaal op zaterdagen: " << counter_dagen_week[5] << ", totaal op zondagen: " << counter_dagen_week[6] << endl;

void countersadd()
{
    counter_afgelopen_dagen[0]++;
    counter_dagen_week[pointerday]++;
    counter_open_total++;
    counter_week_totaal++;
    counter_maand_totaal++;
}

void countersupdate()
{
    counter_week_totaal = 0;
    counter_maand_totaal = 0;
    for (int i = 29; i > 0; i++)
    {
        counter_afgelopen_dagen[i] = counter_afgelopen_dagen[i-1];
        counter_maand_totaal += counter_afgelopen_dagen[i];
    }
    for (int i = 0; i < 7; i++)
    {
        counter_week_totaal += counter_afgelopen_dagen[i];
    }
    pointerday++;
    if (pointerday == 7)
        pointerday = 0;
}