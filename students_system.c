#include <stdio.h>
#include <stdlib.h>

/* Latest student ID */
static int last_stud_id = 0;

#define RSTUD_NOT_NULL root_student != NULL
#define ISTUD_NOT_NULL inserted_student != NULL
#define RSTUD_A_ISTUD_NOT_NULL RSTUD_NOT_NULL && ISTUD_NOT_NULL
#define SEARCH_BY_ID sptr->id == id


typedef struct student {
    int id;
    int age;
    char *name;
    struct student* prev;
    struct student* next;
}student;

/* Create new student */
student* create_student(int age, char* name) {
    student* stud = malloc(sizeof(student));
    stud->id = ++last_stud_id;
    stud->age = age;
    stud->name = name;
}

/* Insert student after */
void insert_last(student* root_student, student* inserted_student) {
    if(RSTUD_A_ISTUD_NOT_NULL) {
        student *sptr = root_student;
        while (sptr->next != NULL) {
            sptr = sptr->next;
        }
        sptr->next = inserted_student;
        inserted_student->prev = sptr;
    }
}

/* Insert student first */
student* insert_first(student* root_student, student* inserted_student) {
    if(RSTUD_A_ISTUD_NOT_NULL) {
        // student *sptr = root_student;
        inserted_student->next = root_student;
        root_student->prev = inserted_student;
        root_student = inserted_student;
        return root_student;
    }
    return root_student;
}

/* Insert student before */
void insert_after_by_id(int id, student* root_student, student* inserted_student) {
    if(RSTUD_A_ISTUD_NOT_NULL) {
        student *sptr = root_student;
        while (sptr != NULL) {
            if(SEARCH_BY_ID) {
                if(sptr->next != NULL) {
                    student* temp_stud = sptr->next;
                    sptr->next = inserted_student;
                    inserted_student->prev = sptr;
                    inserted_student->next = temp_stud;
                    temp_stud->prev = inserted_student;
                    break;
                } else {
                    sptr->next = inserted_student;
                    inserted_student->prev = sptr;
                }
            }
            sptr = sptr->next;
        }
        
    }
}

/* Delete student by id */
void free_student_by_id(int id, student* root_student) {
    if(RSTUD_NOT_NULL) {
        student *sptr = root_student;
        while (sptr != NULL) {
            if(SEARCH_BY_ID) {
                student* prev_stud = sptr->prev;
                student* next_stud = sptr->next;

                if(prev_stud != NULL) {
                    prev_stud->next = next_stud;
                } else {
                    root_student = next_stud;
                }

                if(next_stud != NULL) {
                    next_stud->prev = prev_stud;
                }

                printf("Student %d Deleted!\n",id);
                free(sptr);
                return;
            }
            sptr = sptr->next;
        }
        
    }
    printf("\nStudent %d not found!\n",id);
}

/* Delete students */
void free_students(student* root_student) {
    if(RSTUD_NOT_NULL) {
        student* sptr = root_student;
        student* sptr_to_be_freed = sptr;
        while (sptr != NULL) {
            sptr = sptr->next;
            free(sptr_to_be_freed);
            sptr_to_be_freed = sptr;
        }
    }
    printf("\nStudents Deleted!\n");
}

/* Update age */
void update_age_by_id(int id, int age, student* root_student) {
    if(RSTUD_NOT_NULL) {
        student *sptr = root_student;
        while (sptr != NULL) {
            if(SEARCH_BY_ID) {
                sptr->age = age;
                break;
            }
            sptr = sptr->next;
        }
    }
}

/* Update name */
void update_name_by_id(int id, char* name, student* root_student) {
    if(RSTUD_NOT_NULL) {
        student *sptr = root_student;
        while (sptr != NULL) {
            if(SEARCH_BY_ID) {
                sptr->name = name;
                break;
            }
            sptr = sptr->next;
        }
    }
}

/* Select (print) by id */
void select_by_id(int id, student* root_student) {
    if(RSTUD_NOT_NULL) {
        student *sptr = root_student;
        while (sptr != NULL) {
            if(SEARCH_BY_ID) {
                printf("Student ID: %d\n Student Age: %d\n Student Name: %s\n",
                sptr->id,sptr->age,sptr->name);
                break;
            }
            sptr = sptr->next;
        }
    }
}

/* Select (print) all */
void select_all(student* root_student) {
    if(RSTUD_NOT_NULL) {
        student *sptr = root_student;
        while (sptr != NULL) {
            printf("\nStudent ID: %d\n Student Age: %d\n Student Name: %s\n",
            sptr->id,sptr->age,sptr->name);
            sptr = sptr->next;
        }
    }
}

int main() {

    student* root = create_student(15,"Ahmed Mohammed");
    
    student* s2 = create_student(14,"Naif Saad");

    student* s3 = create_student(16,"Hamed Khaild");

    student* s4 = create_student(17,"Nawaf Jaber");

    student* s5 = create_student(19,"Moahmmed Bader");

    student* s6 = create_student(11,"Ghazi soud");

    insert_last(root,s2);

    insert_last(root,s3);

    insert_after_by_id(3,root,s4);

    root = insert_first(root,s5);

    insert_after_by_id(5,root,s6);

    select_all(root);

    free_student_by_id(3,root);

    printf("----------------------------------------\n");

    update_age_by_id(1,99,root);
    update_name_by_id(3,"nofo dude",root);

    select_all(root);

    free_students(root);

    return 0;
}