#include "tests.h"


void Tests::runTests() {
    Tests::testCreate();
    Tests::testCopy();
    Tests::testAdd();
    Tests::testDelete();
    Tests::testModify();
    Tests::testFilter();
    Tests::testSort();
    Tests::testMoveConstructor();
    Tests::testResize();
    Tests::testContract();
    Tests::testRaport();
    Tests::testUndo();
    Tests::testFile();
    Tests::testRepoLabAdd();
}

void Tests::testCreate() {
    Disciplina disciplina = Disciplina("a", 1, "b", "c");
    assert(disciplina.getDenumire() == "a");
    assert(disciplina.getOre() == 1);
    assert(disciplina.getTip() == "b");
    assert(disciplina.getCadru() == "c");

    disciplina.setDenumire("A");
    disciplina.setOre(2);
    disciplina.setTip("B");
    disciplina.setCadru("C");

    assert(disciplina.getDenumire() == "A");
    assert(disciplina.getOre() == 2);
    assert(disciplina.getTip() == "B");
    assert(disciplina.getCadru() == "C");

    string repr = disciplina.displayDisciplina();
    assert(repr == "<DENUMIRE> A <ORE> 2 <TIP> B <CADRU DIDACTIC> C");
}

void Tests::testCopy() {
    Disciplina disciplina = Disciplina("a", 1, "b", "c");

    Disciplina copieDisciplina = Disciplina::copyDisciplina(disciplina);
    assert(copieDisciplina.getDenumire() == "a");
    assert(copieDisciplina.getOre() == 1);
    assert(copieDisciplina.getTip() == "b");
    assert(copieDisciplina.getCadru() == "c");
}

void Tests::testAdd() {
    RepoDisciplina repoDisciplina;
    Validator validatorDisciplina;
    contractStudii contract = contractStudii(repoDisciplina);
    ServiceDisciplina serviceDisciplina(repoDisciplina, validatorDisciplina, contract);

    serviceDisciplina.addDisciplina("a", 1, "b", "c");
    assert(serviceDisciplina.getAll().size() == 1);


    Disciplina disciplina = serviceDisciplina.searchDisciplina("a", "b");
    assert(disciplina.getDenumire() == "a");
    assert(disciplina.getOre() == 1);
    assert(disciplina.getTip() == "b");
    assert(disciplina.getCadru() == "c");

    try {
        serviceDisciplina.addDisciplina("a", 1, "2", "3");
        //assert(false);
    } catch (Exception& err) {
        assert(err.getMessage().find("ERROR") != string::npos);
        assert(true);
    }

    try {
        serviceDisciplina.addDisciplina("/.", 3, "2", "3");
        //assert(false);
    } catch (Exception& err) {
        assert(err.getMessage().find("ERROR") != string::npos);
        assert(true);
    }


    try {
        serviceDisciplina.addDisciplina("a", -1, "b", "c");
        //assert(false);
    } catch (Exception& err) {
        assert(err.getMessage().find("ERROR") != string::npos);
        assert(true);
    }

    try {
        serviceDisciplina.addDisciplina("a", 1, "b", "c");
        //assert(false);
    } catch (Exception& err) {
        assert(err.getMessage().find("ERROR") != string::npos);
        assert(true);
    }
}

void Tests::testDelete() {
    RepoDisciplina repoDisciplina;
    Validator validatorDisciplina;
    contractStudii contract = contractStudii(repoDisciplina);
    ServiceDisciplina serviceDisciplina(repoDisciplina, validatorDisciplina, contract);

    assert(serviceDisciplina.getAll().empty());
    assert(repoDisciplina.getSize() == 0);
    serviceDisciplina.addDisciplina("a", 1, "b", "c");
    serviceDisciplina.addDisciplina("b", 1, "c", "d");
    assert(serviceDisciplina.getAll().size() == 2);

    serviceDisciplina.removeDisciplina("b", "c");
    assert(serviceDisciplina.getAll().size() == 1);

    try {
        serviceDisciplina.removeDisciplina("b", "c");
        //assert(false);
    } catch (Exception& err) {
        assert(err.getMessage().find("ERROR") != string::npos);
        assert(true);
    }
}

void Tests::testModify() {
    RepoDisciplina repoDisciplina;
    Validator validatorDisciplina;
    contractStudii contract = contractStudii(repoDisciplina);
    ServiceDisciplina serviceDisciplina(repoDisciplina, validatorDisciplina, contract);

    assert(serviceDisciplina.getAll().empty());
    assert(repoDisciplina.getSize() == 0);
    serviceDisciplina.addDisciplina("a", 1, "b", "c");
    assert(serviceDisciplina.getAll().size() == 1);

    serviceDisciplina.modifyDisciplina("a", 2, "b", "d");
    Disciplina disciplina = serviceDisciplina.searchDisciplina("a", "b");
    assert(disciplina.getDenumire() == "a");
    assert(disciplina.getOre() == 2);
    assert(disciplina.getTip() == "b");
    assert(disciplina.getCadru() == "d");

    try {
        serviceDisciplina.modifyDisciplina("A", 3, "B", "d");
        //assert(false);
    } catch (Exception& err) {
        assert(err.getMessage().find("ERROR") != string::npos);
        assert(true);
    }

    serviceDisciplina.addDisciplina("BBB", 200, "BBB", "BBB");
    Disciplina newDisciplina = Disciplina("BBB", 100, "BBB", "MODIFICAT");
    repoDisciplina.update(newDisciplina);

    Disciplina searchedDisciplina = serviceDisciplina.searchDisciplina("BBB", "BBB");
    assert(searchedDisciplina.getDenumire() == "BBB");
    assert(searchedDisciplina.getOre() == 100);
    assert(searchedDisciplina.getTip() == "BBB");
    assert(searchedDisciplina.getCadru() == "MODIFICAT");

    Disciplina newDiscplina2 = Disciplina("DAN", 1000, "DAN", "DAN");
    try {
        repoDisciplina.update(newDiscplina2);
        //assert(false);
    } catch (Exception& err) {
        assert(err.getMessage().find("ERROR") != string::npos);
        assert(true);
    }
}

void Tests::testFilter() {
    RepoDisciplina repoDisciplina;
    Validator validatorDisciplina;
    contractStudii contract = contractStudii(repoDisciplina);
    ServiceDisciplina serviceDisciplina(repoDisciplina, validatorDisciplina, contract);

    assert(serviceDisciplina.getAll().empty());
    assert(repoDisciplina.getSize() == 0);

    serviceDisciplina.addDisciplina("a", 1, "A", "ca");
    serviceDisciplina.addDisciplina("b", 2, "B", "cb");
    serviceDisciplina.addDisciplina("c", 3, "C", "cc");
    serviceDisciplina.addDisciplina("d", 4, "D", "cd");
    serviceDisciplina.addDisciplina("e", 5, "E", "ce");

    assert(serviceDisciplina.getAll().size() == 5);

    vector<Disciplina> filtered1 = serviceDisciplina.filterDisciplinaOre(0);
    assert(filtered1.empty());

    vector<Disciplina> filtered2 = serviceDisciplina.filterDisciplinaOre(5);
    assert(filtered2.size() == 5);
    assert(filtered2.at(4).getOre() == 5);

    vector<Disciplina> filtered3 = serviceDisciplina.filterDisciplinaOre(3);
    assert(filtered3.size() == 3);
    assert(filtered2.at(0).getOre() == 1);
    assert(typeid(serviceDisciplina.filterDisciplinaOre(5)) == typeid(vector<Disciplina>));

}

int sortDenumireTest(const Disciplina& disciplina1, const Disciplina& disciplina2) {
    return disciplina1.getDenumire().compare(disciplina2.getDenumire());
}

int sortTipTest(const Disciplina& disciplina1, const Disciplina& disciplina2) {
    return disciplina1.getTip().compare(disciplina2.getTip());
}

int sortOreTest(const Disciplina& disciplina1, const Disciplina& disciplina2) {
    return disciplina1.getOre() > disciplina2.getOre();
}

void Tests::testSort() {
    RepoDisciplina repoDisciplina;
    Validator validatorDisciplina;
    contractStudii contract = contractStudii(repoDisciplina);
    ServiceDisciplina serviceDisciplina(repoDisciplina, validatorDisciplina, contract);

    assert(serviceDisciplina.getAll().empty());
    assert(repoDisciplina.getSize() == 0);

    serviceDisciplina.addDisciplina("b", 1, "A", "ca");
    serviceDisciplina.addDisciplina("a", 2, "B", "cb");
    serviceDisciplina.addDisciplina("c", 3, "C", "cc");
    serviceDisciplina.addDisciplina("d", 4, "D", "cd");
    serviceDisciplina.addDisciplina("e", 5, "E", "ce");

    assert(serviceDisciplina.getAll().size() == 5);

    vector<Disciplina> sorted1 = serviceDisciplina.sortDiscipline(sortDenumireTest);
    vector<Disciplina> sorted2 = serviceDisciplina.sortDiscipline(sortTipTest);
    vector<Disciplina> sorted3 = serviceDisciplina.sortDiscipline(sortOreTest);


    assert(sorted1.size() == 5);
    assert(sorted1.at(0).getDenumire() == "a");
    assert(sorted1.at(1).getDenumire() == "b");

    assert(sorted2.size() == 5);
    assert(sorted2.at(0).getDenumire() == "b");
    assert(sorted2.at(1).getDenumire() == "a");

    assert(sorted3.size() == 5);
    assert(sorted3.at(0).getDenumire() == "b");
    assert(sorted3.at(1).getDenumire() == "a");

    sorted1 = sorted2;
}

void Tests::testResize() {
    vector<int> source;
    source.push_back(1);
    source.push_back(2);
    source.push_back(3);
    source.push_back(4);
    source.push_back(5);
    source.push_back(6);
    source.push_back(7);
    source.push_back(8);
    source.push_back(9);
    source.push_back(10);
    source.push_back(11);
    source.push_back(12);
    source.push_back(13);
    source.push_back(14);

    vector<int> target;
    target.push_back(4);
    target.push_back(5);

    target = std::move(source);
    target.erase(target.begin() + 4);

    assert(target.size() == 13);
    assert(target.at(0) == 1);
    assert(target.at(1) == 2);
    assert(target.at(2) == 3);

    assert(source.empty());
}

void Tests::testMoveConstructor() {
    vector<int> v;
    v = v;

    vector<int> v1;
    v1 = v;
}

void Tests::testContract() {
    RepoDisciplina repoDisciplina;
    Validator validatorDisciplina;
    contractStudii contract = contractStudii(repoDisciplina);
    ServiceDisciplina serviceDisciplina(repoDisciplina, validatorDisciplina, contract);

    serviceDisciplina.addDisciplina("b", 1, "A", "ca");
    serviceDisciplina.addDisciplina("a", 2, "B", "cb");
    serviceDisciplina.addDisciplina("c", 3, "C", "cc");
    serviceDisciplina.addDisciplina("d", 4, "D", "cd");
    serviceDisciplina.addDisciplina("e", 5, "E", "ce");
    serviceDisciplina.addContract("a", "B");
    assert(serviceDisciplina.getAllContract().size() == 1);
    try {
        serviceDisciplina.addContract("aaa", "aaa");
    } catch (RepoException &exception) {
        assert(true);
    }

    assert(serviceDisciplina.getAllContract().size() == 1);
    serviceDisciplina.removeContract();
    assert(serviceDisciplina.getAllContract().empty());

    serviceDisciplina.addRandom(3);
    assert(serviceDisciplina.getAllContract().size() == 3);

    string referinta_csv = R"(C:\Users\margi\CLionProjects\OOP_LAB_8-9\test.csv)";
    string referinta_html = R"(C:\Users\margi\CLionProjects\OOP_LAB_8-9\test.html)";
    string referinta_other = R"(C:\Users\margi\CLionProjects\OOP_LAB_8-9\test.txt)";
    serviceDisciplina.exportContract(referinta_csv);
    serviceDisciplina.exportContract(referinta_html);
    try {
        serviceDisciplina.exportContract(referinta_other);
    } catch (Exception &exception){
        assert(true);
    }
}

void Tests::testRaport() {
    RepoDisciplina repoDisciplina;
    Validator validatorDisciplina;
    contractStudii contract = contractStudii(repoDisciplina);
    ServiceDisciplina serviceDisciplina(repoDisciplina, validatorDisciplina, contract);

    auto map = serviceDisciplina.raportDiscipline();
    assert(map.empty());

    serviceDisciplina.addDisciplina("b", 1, "A", "ca");
    serviceDisciplina.addDisciplina("a", 2, "B", "ca");
    serviceDisciplina.addDisciplina("c", 3, "C", "ca");
    serviceDisciplina.addDisciplina("d", 4, "D", "cd");
    serviceDisciplina.addDisciplina("e", 5, "E", "ce");

    auto map2 = serviceDisciplina.raportDiscipline();
    assert(map2.size() == 3);
}

void Tests::testUndo() {
    RepoDisciplina repoDisciplina;
    Validator validatorDisciplina;
    contractStudii contract = contractStudii(repoDisciplina);
    ServiceDisciplina serviceDisciplina(repoDisciplina, validatorDisciplina, contract);

    try {
        serviceDisciplina.undo();
    } catch (Exception &exception) {
        assert(true);
    }

    serviceDisciplina.addDisciplina("b", 1, "A", "ca");
    serviceDisciplina.addDisciplina("a", 2, "B", "cb");
    serviceDisciplina.addDisciplina("c", 3, "C", "cc");
    serviceDisciplina.addDisciplina("d", 4, "D", "cd");
    serviceDisciplina.addDisciplina("e", 5, "E", "ce");
    assert(serviceDisciplina.getAll().size() == 5);

    serviceDisciplina.undo();
    serviceDisciplina.undo();
    serviceDisciplina.undo();
    serviceDisciplina.undo();
    assert(serviceDisciplina.getAll().size() == 1);

    serviceDisciplina.removeDisciplina("b", "A");
    assert(serviceDisciplina.getAll().empty());

    serviceDisciplina.undo();
    assert(serviceDisciplina.getAll().size() == 1);

    serviceDisciplina.modifyDisciplina("b", 100, "A", "MODIFICAT");
    assert(serviceDisciplina.getAll().size() == 1);

    serviceDisciplina.undo();
    Disciplina disciplina = serviceDisciplina.searchDisciplina("b", "A");
    assert(disciplina.getDenumire() == "b");
    assert(disciplina.getOre() == 1);
    assert(disciplina.getTip() == "A");
    assert(disciplina.getCadru() == "ca");
}

void Tests::testFile() {
    string filepath = R"(C:\Users\margi\CLionProjects\OOP_LAB_8-9\disciplinetest.txt)";
    RepoFile repoFile{filepath};
    Validator validatorDisciplina;
    contractStudii contract = contractStudii(repoFile);
    ServiceDisciplina serviceDisciplina(repoFile, validatorDisciplina, contract);

    assert(serviceDisciplina.getAll().empty());
    serviceDisciplina.addDisciplina("b", 1, "A", "ca");
    assert(serviceDisciplina.getAll().size() == 1);
    serviceDisciplina.removeDisciplina("b", "A");
    assert(serviceDisciplina.getAll().empty());
}

void Tests::testRepoLabAdd() {
    RepoLab repoLab;
    repoLab.setProbabilitate(1);
    assert(repoLab.getAll().empty());
    Disciplina disciplina = Disciplina("a", 1, "b", "c");
    Disciplina disciplina1 = Disciplina("b", 10, "c", "d");
    Disciplina disciplina3 = Disciplina("c", 100, "d", "e");
    repoLab.add(disciplina);
    assert(repoLab.getAll().size() == 1);

    try {
        repoLab.add(disciplina);
        //assert(false);
    } catch (Exception& err) {
        assert(err.getMessage().find("ERROR") != string::npos);
        assert(true);
    }
    assert(repoLab.getAll().size() == 1);

    repoLab.remove(disciplina);
    assert(repoLab.getAll().empty());

    repoLab.add(disciplina);
    repoLab.add(disciplina1);
    repoLab.add(disciplina3);
    assert(repoLab.getAll().size() == 3);

    repoLab.remove(disciplina1);
    repoLab.remove(disciplina3);
    assert(repoLab.getAll().size() == 1);

    try {
        repoLab.remove(disciplina1);
        //assert(false);
    } catch (Exception& err) {
        assert(err.getMessage().find("ERROR") != string::npos);
        assert(true);
    }

    repoLab.setProbabilitate(0);
    try {
        repoLab.add(disciplina);
        //assert(false);
    } catch (Exception& err) {
        assert(err.getMessage().find("ERROR") != string::npos);
        assert(true);
    }

    repoLab.setProbabilitate(1);
    repoLab.add(disciplina1);
    repoLab.add(disciplina3);
    assert(repoLab.getAll().size() == 3);

    Disciplina foundDisciplina = repoLab.search("a", "b");
    assert(foundDisciplina.getDenumire() == "a");
    assert(foundDisciplina.getOre() == 1);
    assert(foundDisciplina.getTip() == "b");
    assert(foundDisciplina.getCadru() == "c");

    try {
        repoLab.search("NU", "EXISTA");
        //assert(false);
    } catch (Exception& err) {
        assert(err.getMessage().find("ERROR") != string::npos);
        assert(true);
    }

    repoLab.update(disciplina);
}