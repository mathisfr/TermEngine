# 🚀 TermEngine

Une petite bibliothèque C++ pour apprendre à créer une **bibliothèque graphique dans le terminal**.

TermEngine est avant tout un projet personnel réalisé **en quelques jours, juste pour le fun et pour apprendre**. Le but était d'expérimenter avec le rendu 2D dans un terminal et de voir comment structurer un petit projet de ce type.

Le projet n'a pas vocation à devenir une bibliothèque complète ou activement maintenue. Je ne prévois pas forcément de revenir dessus, **sauf si l'envie me reprend de l'améliorer**.

---

## 🎯 Objectif du projet

L'objectif principal de TermEngine était d'apprendre et d'expérimenter autour de plusieurs concepts :

* 🎨 Créer un système de rendu 2D dans le terminal.
* 🧩 Réfléchir à la structure d'une petite bibliothèque graphique.
* 🖥️ Expérimenter avec l'affichage d'éléments graphiques directement dans un terminal.
* ⚙️ Comprendre les différentes contraintes liées au rendu dans un terminal.

Le projet a donc avant tout une vocation **expérimentale et éducative**.

---

## 🧪 État actuel

Le projet fonctionne, mais il reste très limité et contient plusieurs choix d'architecture qui pourraient être améliorés.

Il a été développé et testé principalement sur **MacBook Air M4 (macOS)**.

L'un des principaux points à améliorer concerne la **gestion de la taille de la fenêtre**.

Actuellement, la taille est gérée à travers une *template*, ce qui est lié à la façon dont l'architecture du projet a été construite. Cette approche implique qu'une seule taille de fenêtre fixe puisse être utilisée.

C'est probablement le plus gros point que je reverrais dans l'architecture : permettre de définir la taille de la fenêtre dynamiquement plutôt que de la déterminer à travers une *template*.

---

## 🛠️ Ce qui pourrait être amélioré

Quelques pistes possibles si je décide de reprendre le projet :

* Permettre une taille de fenêtre dynamique.
* Revoir l'architecture autour de la gestion de la fenêtre.
* Améliorer le système de rendu.
* Ajouter davantage de fonctionnalités graphiques.
* Améliorer la portabilité vers Linux et Windows.
* Nettoyer et simplifier certaines parties du code.

Aucune de ces améliorations n'est cependant planifiée pour le moment.

---

## 🤝 Contribution

Le projet étant principalement un **projet personnel d'apprentissage**, je ne prévois pas particulièrement de le maintenir activement.

Les *Issues* et *Pull Requests* restent toutefois les bienvenues si quelqu'un souhaite expérimenter, proposer une amélioration ou simplement jouer avec le projet.
