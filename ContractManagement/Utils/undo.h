#pragma once
#include "../Domain/disciplina.h"
#include "../Repository/repository.h"

/**
 * @brief Abstract class representing an undo action.
 *
 * This class serves as a base for any undo action. It declares a virtual `doUndo` function that must be implemented
 * by its derived classes to undo a specific action (e.g., adding, removing, or modifying a `Disciplina` object).
 */
class ActiuneUndo {
public:
    /**
     * @brief Executes the undo action.
     *
     * This function is a pure virtual function and must be overridden by the derived classes to undo the action
     * that was performed.
     */
    virtual void doUndo() = 0;

    /**
     * @brief Default virtual destructor.
     */
    virtual ~ActiuneUndo() = default;
};

/**
 * @brief Undo action for adding a `Disciplina` object to the repository.
 *
 * This class represents the action of undoing an add operation, i.e., removing the `Disciplina` object from the repository.
 */
class undoAdd : public ActiuneUndo {
private:
    Disciplina addedDisciplina; ///< The `Disciplina` that was added.
    RepoAbstract& repoDisciplina; ///< Reference to the repository where the `Disciplina` was added.

public:
    /**
     * @brief Constructor for `undoAdd`.
     *
     * Initializes the undo action with the `Disciplina` that was added and the repository.
     *
     * @param repoDisciplina A reference to the repository where the `Disciplina` was added.
     * @param addedDisciplina The `Disciplina` object that was added.
     */
    undoAdd(RepoAbstract& repoDisciplina, const Disciplina& addedDisciplina)
            : addedDisciplina{addedDisciplina}, repoDisciplina{repoDisciplina} {}

    /**
     * @brief Undoes the add operation.
     *
     * Removes the `Disciplina` that was previously added to the repository.
     */
    void doUndo() override {
        repoDisciplina.remove(addedDisciplina);
    }
};

/**
 * @brief Undo action for removing a `Disciplina` object from the repository.
 *
 * This class represents the action of undoing a remove operation, i.e., adding the `Disciplina` object back to the repository.
 */
class undoRemove : public ActiuneUndo {
private:
    Disciplina removedDisciplina; ///< The `Disciplina` that was removed.
    RepoAbstract& repoDisciplina; ///< Reference to the repository where the `Disciplina` was removed from.

public:
    /**
     * @brief Constructor for `undoRemove`.
     *
     * Initializes the undo action with the `Disciplina` that was removed and the repository.
     *
     * @param repoDisciplina A reference to the repository where the `Disciplina` was removed from.
     * @param removedDisciplina The `Disciplina` object that was removed.
     */
    undoRemove(RepoAbstract& repoDisciplina, Disciplina& removedDisciplina)
            : removedDisciplina{removedDisciplina}, repoDisciplina{repoDisciplina} {}

    /**
     * @brief Undoes the remove operation.
     *
     * Adds the `Disciplina` that was previously removed back to the repository.
     */
    void doUndo() override {
        repoDisciplina.add(removedDisciplina);
    }
};

/**
 * @brief Undo action for modifying a `Disciplina` object in the repository.
 *
 * This class represents the action of undoing a modify operation, i.e., restoring the original `Disciplina` object
 * in place of the modified one.
 */
class undoModify : public ActiuneUndo {
private:
    Disciplina newDisciplina; ///< The modified `Disciplina`.
    Disciplina oldDisciplina; ///< The original `Disciplina` before modification.
    RepoAbstract& repoDisciplina; ///< Reference to the repository where the modification took place.

public:
    /**
     * @brief Constructor for `undoModify`.
     *
     * Initializes the undo action with the modified `Disciplina`, the original `Disciplina`, and the repository.
     *
     * @param repoDisciplina A reference to the repository where the modification took place.
     * @param newDisciplina The modified `Disciplina`.
     * @param oldDisciplina The original `Disciplina` before modification.
     */
    undoModify(RepoAbstract& repoDisciplina, Disciplina& newDisciplina, Disciplina& oldDisciplina)
            : newDisciplina{newDisciplina}, oldDisciplina{oldDisciplina}, repoDisciplina{repoDisciplina} {}

    /**
     * @brief Undoes the modify operation.
     *
     * Removes the modified `Disciplina` and restores the original `Disciplina` to the repository.
     */
    void doUndo() override {
        repoDisciplina.remove(newDisciplina);
        repoDisciplina.add(oldDisciplina);
    }
};
