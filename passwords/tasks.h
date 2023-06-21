#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <mpi.h>
#include "linkedlist.h"
#include "hashtable.h"
#include "stringmanipulation.h"
#include "stringlist.h"
#include "pw_helpers.h"
//function that will run all the tasks in parallel
void doWork(int task, struct users users, struct stringList *top250, struct stringList *books, struct stringList *years);