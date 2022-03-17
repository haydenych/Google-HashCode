# Google HashCode 2022 Qualifications

This is my attempt to the HashCode 2022 Qualification Round. The code here is refactored for readability. Some bugs are fixed as well.

### My scores during competition

A: 33
B: 310676
C: 21783
D: 50165
E: 1367637
F: 254572

Total: 2004866
Rank: 1939

### My scores after competition, in practice mode

A: 33, example
B: 310676, mode = 2, threshold = 0, useMentor = true
B: 310676, mode = 4, threshold = 0, useMentor = true
C: 203315, mode = 0, threshold = 0, useMentor = false
D: 50165, mode = 0, threshold = 0, useMentor = false
E: 1637258, mode = 1, threshold = 0, useMentor = true
F: 475082, mode = 1, threshold = 0 , useMentor = true

Total: 2676529

### Approach

I attempted several greedy approaches. They are,
* Mode 0. Add Projects by descending order of scores
* Mode 1. Add Projects by increasing order of "best before" for the project
* Mode 2. Add Projects by increasing order of number of roles required by the project
* Mode 3. Add Projects by the number of days it takes to complete the project
* Mode 4. Add Projects by its score to role ratio

(See line 157 in code).

### Some suggested improvements and TODOs

* Add a function to calculate scores locally given an output.

* Add ways to replace the old contributor with a new one for improvement.

    - If the contributor's available time is earlier, replace the old contributor with the new one. This allows the project to start earlier.
    - If the contributor fits the requirements and has a skill level closer to the required level, replace the old contributor with the new one. This avoids wasting a contributor with a high skill level on a project that only requires low skill levels.

    Note that the two above mentioned ways of improvement may contradict with one another.

* Allow replacing contributors that have been chosen earlier with new ones. (See line 213 in code). This may cause certain requirements to fail, so checking is needed.

* Allow duplicate roles in the same project taking different required levels. (See line 111 in code).


