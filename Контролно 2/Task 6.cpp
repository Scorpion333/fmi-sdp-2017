struct Cell {
    int data;
    Cell *right, *down;
};

bool negative_under(Cell* cell) {
    if (cell == nullptr) {
        return false;
    }
    return cell->data < 0 || negative_under(cell->down);
}

// Works only for non-empty cells (but I don't call it with nullptr, so it's OK)
void delete_cell_right_from(Cell* cell) {
    Cell* temp = cell->right;
    cell->right = cell->right->right;
    delete temp;
}

void delete_column_right_from(Cell* cell) {
    if (cell == nullptr) {
        return;
    }
    delete_column_right_from(cell->down);
    delete_cell_right_from(cell);
}

void delete_leftest_column(Cell*& M) {
    if (M == nullptr) {
        return;
    }
    delete_leftest_column(M->down);
    Cell* top = M;                      // Top of leftest column
    M = top->right;
    delete top;
}

// Deletes all columns containing negative number
void deleteNegative(Cell*& M) {
    if (M == nullptr) {
        return;
    }
    Cell* column_top = M;               // For iterating through the columns

    while (column_top->right != nullptr) {
        if (negative_under(column_top->right))
            delete_column_right_from(column_top);
        else
            column_top = column_top->right;
    }
    if (negative_under(M)) {
        delete_leftest_column(M);
    }
}