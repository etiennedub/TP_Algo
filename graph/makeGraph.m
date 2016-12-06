complexFile = 'complex.csv';
monceauFile = 'monceau.csv';
complex = csvread(complexFile,1);
monceau = csvread(monceauFile,1);

% ------ Monceau --------
n = monceau(:,1);
ajout = monceau(:,2);
supp = monceau(:,3);
dim = monceau(:,4);
get = monceau(:,5);
theorique = 20*log10(n);


figure('Name', 'Monceau');
subplot(1,2,1);
plot(n,theorique, 'LineWidth',3);
hold on;
plot(n, supp, 'LineWidth',3);
axis([0 7500 0 350])
legend('20*log(n)','SuprimmerMin()')
xlabel('Nombre de noeuds','LineWidth',3);
ylabel('Temps (μs)');
title('Temps d''exécution de la fonction supprimerMin()')

% ------ Complex --------
n = complex(:,1);
meilleur = complex(:,2);
bellman = complex(:,3);
dijkstra = complex(:,4);
theorique = n.*log10(n);

subplot(1,2,2);
plot(n, dijkstra,'LineWidth',3); 
hold on;
plot(n, meilleur,'LineWidth',3);
plot(n,bellman,'LineWidth',3);
plot(n, theorique,'LineWidth',3);
xlabel('Nombre de sommets','LineWidth',3);
ylabel('Temps (μs)');
legend('Dijkstra','Meilleur', 'Bellman', 'n*log(n)');
axis([0 5000 0 100000]);
title('Comparaison des différents algorithmes')


