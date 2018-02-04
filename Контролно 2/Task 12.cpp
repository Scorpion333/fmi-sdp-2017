// Not the most efficient and short solution, but a working and (I hope) understandable one.

struct Cell {
    int data;
    Cell *right, *down;
    Cell(int _data, Cell* _right, Cell* _down) : data(_data), right(_right), down(_down) {}
};


void find_row_and_col_of_max(Cell* m, Cell*& row_of_max, Cell*& col_of_max) {
    row_of_max = col_of_max = m;                    // It is better if the initialization of these two
                                                    // is in the function. Remember task 2 from 6.01.2018?
    int max = m->data;
    Cell* row_start = m;
    while (row_start != nullptr) {
        Cell* crr = row_start;
        Cell* crr_in_first_row = m;
        while (crr != nullptr) {
            if (crr->data > max) {
                max = crr->data;
                row_of_max = row_start;
                col_of_max = crr_in_first_row;
            }
            crr = crr->right;
            crr_in_first_row = crr_in_first_row->right;
        }
        row_start = row_start->down;                // My mistake was that I had forgotten to write 'row_start ='
    }
}


// Functions for copying:

Cell* copy_of_row(Cell* row) {
    if (row == nullptr) {
        return nullptr;
    }
    return new Cell(row->data, copy_of_row(row->right), nullptr);
}

void add_row(Cell*& m, Cell* row) {
    Cell* new_row = copy_of_row(row);
    if (m == nullptr) {
        m = new_row;
        return;
    }
    if (m->down == nullptr) {
        Cell* crr_in_m = m;
        Cell* crr_in_new_row = new_row;
        while (crr_in_m != nullptr) {
            crr_in_m->down = crr_in_new_row;
            crr_in_m = crr_in_m->right;
            crr_in_new_row = crr_in_new_row->right;
        }
        return;
    }
    add_row(m->down, new_row);
}

Cell* copy_of_matrix(Cell* M) {
    Cell* new_matrix = nullptr;
    Cell* crr_row = M;
    while (crr_row != nullptr) {
        add_row(new_matrix, crr_row);
        crr_row = crr_row->down;
    }
    return new_matrix;
}


// Functions for deleting:

void delete_first_row(Cell*& m) {
    if (m == nullptr)
        return;
    delete_first_row(m->right);
    Cell* temp = m;
    m = m->down;
    delete temp;
}
void delete_first_col(Cell*& m) {
    if (m == nullptr)
        return;
    delete_first_col(m->down);
    Cell* temp = m;
    m = m->right;
    delete temp;
}

Cell* row_above(Cell* row, Cell* m) {
    while (m->down != row)
        m = m->down;
    return m;
}
Cell* col_left_from(Cell* col, Cell* m) {
    while (m->right != col)
        m = m->right;
    return m;
}

void delete_row(Cell*& m, Cell* deleted_row) {
    Cell* above_row = row_above(deleted_row, m);
    for (Cell* crr = above_row; crr != nullptr; crr = crr->right) {
        Cell* temp = crr->down;
        crr->down = crr->down->down;
        delete temp;
    }
}
void delete_col(Cell*& m, Cell* deleted_col) {
    Cell* left_col = col_left_from(deleted_col, m);
    for (Cell* crr = left_col; crr != nullptr; crr = crr->down) {
        Cell* temp = crr->right;
        crr->right = crr->right->right;
        delete temp;
    }
}


Cell* buildAdjungate(Cell* M) {
    Cell* new_matrix = copy_of_matrix(M);
    
    Cell* row_of_max;
    Cell* col_of_max;
    find_row_and_col_of_max(new_matrix, row_of_max, col_of_max);

    if (row_of_max == new_matrix && col_of_max == new_matrix) {
        delete_first_row(new_matrix);
        delete_first_col(new_matrix);
    }
    else if (row_of_max == new_matrix) {
        delete_col(new_matrix, col_of_max);
        delete_first_row(new_matrix);
    }
    else if (col_of_max == new_matrix) {
        delete_row(new_matrix, row_of_max);
        delete_first_col(new_matrix);
    }
    else {
        delete_row(new_matrix, row_of_max);
        delete_col(new_matrix, col_of_max);
    }
    return new_matrix;
}
