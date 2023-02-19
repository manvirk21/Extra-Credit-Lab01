// Importing the standard input/output library.
#include <stdio.h>

// Declaring a constant variable called `DEPARTMENTS` and assigning it the value `5`.
const int DEPARTMENTS = 5;
// Declaring a constant variable called `PROGRAMMERS` and assigning it the value `5`.
const int PROGRAMMERS = 5;

/* It loops through each department, and for each department it loops through each programmer, and for
 each programmer it checks if the programmer is available, and if so it assigns the programmer to the
 department, and if not it checks if the programmer prefers the current department to the department
 they're already assigned to, and if so it reassigns the programmer to the current department
 The number of departments that are assigned to a programmer is returned */
int main() {
  // Declare variables to store department and programmer preferences
  // Declaring a 2D array of integers called `dept_pref` with `DEPARTMENTS` rows and `PROGRAMMERS` columns.
  int dept_pref[DEPARTMENTS][PROGRAMMERS];
  // Declaring a 2D array of integers called `prog_pref` with `PROGRAMMERS` rows and `DEPARTMENTS` columns.
  int prog_pref[PROGRAMMERS][DEPARTMENTS];

  // Read preferences from input file
  // Declaring a variable called `filename` that is an array of 100 characters.
  char filename[100];
  // Printing the string to the console.
  printf("Enter file name: ");
  // Reading a string from the console and storing it in the variable `filename`.
  scanf("%s", filename);
  // Opening a file with the name `filename` and storing it in the variable `file`.
  FILE *file = fopen(filename, "r");
  // Checking if the file is null, and if so it prints an error message and returns 1.
  if (file == NULL) {
    // It prints the string to the console.
    printf("Unable to open file\n");
    // It returns the value 1 to the operating system.
    return 1;
  }
  // Looping through each department.
  for (int i = 0; i < DEPARTMENTS; i++) {
    // Looping through each programmer.
    for (int j = 0; j < PROGRAMMERS; j++) {
      // It reads an integer from the file and stores it in the variable `dept_pref[i][j]`.
      fscanf(file, "%d", &dept_pref[i][j]);
    }
  }
  // Looping through each programmer.
  for (int i = 0; i < PROGRAMMERS; i++) {
    // It's looping through each department.
    for (int j = 0; j < DEPARTMENTS; j++) {
      // It reads an integer from the file and stores it in the variable `prog_pref[i][j]`.
      fscanf(file, "%d", &prog_pref[i][j]);
    }
  }
  // It closes the file.
  fclose(file);

  // It's declaring an array of integers called `dept_assign` with `DEPARTMENTS` elements.
  int dept_assign[DEPARTMENTS];
  // It's declaring an array of integers called `prog_assign` with `PROGRAMMERS` elements.
  int prog_assign[PROGRAMMERS];

  // Initialize assignments to -1 (unassigned)
  for (int i = 0; i < DEPARTMENTS; i++) { // It's looping through each department.
    dept_assign[i] = -1;
  }
  // It's looping through each programmer.
  for (int i = 0; i < PROGRAMMERS; i++) {
    // It's assigning the value `-1` to the element at index `i` of the array `prog_assign`.
    prog_assign[i] = -1;
  }

  // Assigning each department a programmer
  for (int i = 0; i < DEPARTMENTS; i++) {
    // It's looping through each programmer to check the department's preferences in order.
    for (int j = 0; j < PROGRAMMERS; j++) {
      // It's subtracting 1 from the value at index `j` of the array `dept_pref[i]` and storing it in the variable `prog_id`.
      int prog_id = dept_pref[i][j] - 1; // convert to 0-indexed
      // It's checking if the programmer is available.
      if (prog_assign[prog_id] == -1) {
        // Programmer is available, so assign to department
        dept_assign[i] = prog_id;
        // It's assigning the value of `i` to the element at index `prog_id` of the array `prog_assign`.
        prog_assign[prog_id] = i;
        // It's breaking out of the current loop.
        break;
      } else {
        // Programmer is already assigned, so check preferences
        int curr_dept = prog_assign[prog_id];
        // It's declaring two variables called `pref_in_curr_dept` and `pref_in_new_dept` and assigning them the value `-1`.
        int pref_in_curr_dept = -1, pref_in_new_dept = -1;
        // It's looping through each department.
        for (int k = 0; k < DEPARTMENTS; k++) {
          // It's checking if the value at index `k` of the array `prog_pref[prog_id]` is equal to the value of `curr_dept` plus 1.
          if (prog_pref[prog_id][k] == curr_dept + 1) {
            // It's assigning the value of `k` to the variable `pref_in_curr_dept`.
            pref_in_curr_dept = k;
          }
          // It's checking if the value at index `k` of the array `prog_pref[prog_id]` is equal to the value of `i` plus 1.
          if (prog_pref[prog_id][k] == i + 1) {
            // It's assigning the value of `k` to the variable `pref_in_new_dept`.
            pref_in_new_dept = k;
          }
        }
        // It's checking if the new department is higher on the programmer's preferences than the current department.
        if (pref_in_new_dept < pref_in_curr_dept) {
          // New department is higher on programmer's preferences, so reassign
          dept_assign[curr_dept] = -1;
          dept_assign[i] = prog_id;
          prog_assign[prog_id] = i;
          // It's breaking out of the current loop.
          break;
        }
      }
    }
  }

  // Print out department assignments
  printf("Department assignments:\n");
  // It's looping through each department.
  for (int i = 0; i < DEPARTMENTS; i++) {
    printf("Department %d assigned Programmer %d\n", i + 1, dept_assign[i] + 1);
  }
}
