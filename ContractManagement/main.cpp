#include "Repository/repository.h"
#include "Service/service.h"
#include "Console/ui.h"
#include "Validators/validator.h"
#include "Tests/tests.h"
#include "Contract/contract.h"
#include "Controller/GUI.h"


// Main function of program.
int main(int argc, char* argv[]) {
    Tests::runTests();

    QApplication gestiuneDiscipline(argc, argv);
    QFont font("AnyStyle");
    QApplication::setFont(font);

    string filename = R"(C:\Users\margi\CLionProjects\OOP_LAB_13-14\Data\discipline.txt)";

    RepoFile repoFile = RepoFile(filename);
    RepoDisciplina repoDisciplina = RepoDisciplina();
    RepoLab repoLab = RepoLab();
    repoLab.setProbabilitate(1.0);

    Validator validatorDisciplina = Validator();
    contractStudii contract = contractStudii(repoDisciplina);
    ServiceDisciplina serviceDisciplina = ServiceDisciplina(repoFile, validatorDisciplina, contract);

    //Console console = Console(serviceDisciplina); // NOLINT(*-use-auto)
    //console.run();

    ContracteGUI gui = ContracteGUI(serviceDisciplina);
    gui.show();
    return QApplication::exec();
}
