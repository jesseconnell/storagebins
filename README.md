# storagebins
This is my solution to a problem my wife saw on a facebook post.  It's a perfect [ProjectEuler](https://projecteuler.net/)-style problem, so I figured I'd solve it both analytically and verify with a program.

****Problem****
There are four colors of buckets.  For each color, there are two single-width buckets ("singles") and one double-width bucket ("doubles").  (So, for example, you have one 2-unit wide green buckets and two 1-unit green buckets.)  Four colors, three buckets apiece, gives a total of 12 buckets.

![alt text][Rack]

There is a rack with four shelves, each shelf holding a total width of four units.  How many unique arrangements can you make such that all buckets are used, all shelves are full?

****Solution****

**First, ignore colors completely** and enumerate the possible arrangements only in terms of bucket sizes.  The various arrangements are:

| Type      | Composition          |                        |
| :-------: |:--------------------:| :----------------------|
| `I`       | 4 singles            | ![alt text][TypeIg]    |
| `II`      | 2 doubles            | ![alt text][TypeIIg]   |
| `III`     | 1 double + 2 singles | ![alt text][TypeIIIg]  |

There are constraints on the combinations of rows possible.  (E.g., we cannot have four rows of type `I`).  We can just enumerate the possibilities, ignoring order (for now):

| Case | Shelf combination           |                                                     |
|:----:|:--------------------------- |:--------------------------------------------------- |
| (1)  | `I`, `I`, `II`, `II`        | All 4 doubles on two shelves                        |
| (2)  | `I`, `II`, `III`, `III`     | 2 doubles on one shelf, other 2 on separate shelves |
| (3)  | `III`, `III`, `III`, `III`  | Each shelf has 1 double, 2 singles                  |

We count the variations of each of these cases separately and add them together.  Counting variations, we first consider the *row variations* (**P**) ignoring the sub-cases of Type `III` shelves.  Then we multiply this by a factor **F** which accounts for variations of Type `III` shelves.  Since each Type `III` shelf has `3` variations, if there are `N` shelves, then there are `3^N` variations.  

* In *Case (1)* there are none, so we use `F=3^0 = 1` (makes sense if you think about it)
* In *Case (2)* there are `2`, so we use `F=3^2 = 9`
* In *Case (3)* there are `4`, so we use `F=3^4 = 81`


| Case | Row Permutations               | P      | Type `III` Shelves  | F *(`=3^P`)*    | Total Variations `= P*F`   |
| :---:| :----------------------------- |:------:|:--------------------|:----------------|:----------------- |
| (1)  | `4!/(2! * 2!)` *(4 choose 2)*  | `6`    | `0`                 | `1`             | **`6`**           |
| (2)  | `4!/2!` *see note*             | `12`   | `2`                 | `9` *(`=3^2`)*  | **`108`**         |
| (3)  | `1`                            | `1`    | `4`                 | `81` *(`=3^4`)* | **`81`**          |

*Note: this is also (4 choose 2,1,1), using the "multinomial coefficient" discussed below"*

Adding all these cases together, we get `6 + 108 + 81 = `**`195`**.  (Another way to think about this is if all buckets were the same color, this would be the total number of configurations for the rack.)

Next, for each of the 195 shape-arrangements above, we **account for color ordering variations**.

To make this "simple", we can count the colorings of the doubles separately from the colorings of the singles, then take the product (since they're independent):

* **doubles:**  This one's simple:  `4! = 24`
* **singles:**  Basically, we're asking how many ways you can arrange 1,1,2,2,3,3,4,4 ?  
The answer is to use the *multinomial coefficient*, `(8 choose 2,2,2,2) = 40320/(2*2*2*2) = 2520`.  
(Multinomial coefficients are similar to binomial coefficients, "P choose Q", but a bit more involved.  See [wikipedia's explanation](https://en.wikipedia.org/wiki/Multinomial_theorem#Ways_to_put_objects_into_bins) or this [good youtube video](https://www.youtube.com/watch?v=rYtzhc2snj4) ).

The product is `24 * 2520 = 60,480`
Multiply this by the number of "shape arrangements" above:

`195 * 60,480 =`

**`11,793,600`**

****Brute Force Verification****

The C++ program in this repo yields the same solution by brute-force.

**Approach**

Using [Heap's Algorithm](https://en.wikipedia.org/wiki/Heap%27s_algorithm), consider **all possible orderings of the 12 buckets**.  For each ordering, check if:

1. Each shelf contains a total of 4 units - i.e., You cannot have a single followed by two doubles on a shelf.
2. To avoid double-counting when, e.g., two orderings differ only because two like-colored single buckets are switched, we have IDs for all 12 buckets, such that `ID0` and `ID1` are the pair of color #1, `ID3` and `ID4` are the pair of color #2, etc.  If we see the ordering have `ID0` come after `ID1` (or `ID3` after `ID4`, etc, etc), we do not count the ordering as valid.  (Maybe my explanation isn't clear, but I could make a smaller example to demonstrate this.  :-)

Anyway, as we go through all `12!` permutations of the buckets, and tally up each time the above are met, we get the same answer, **`11,793,600`**

[TypeI]: https://raw.githubusercontent.com/jesseconnell/storagebins/master/images/Type_I.png "TypeI - s s s s"
[TypeII]: https://raw.githubusercontent.com/jesseconnell/storagebins/master/images/Type_II.png "TypeII - D D"
[TypeIIIa]: https://raw.githubusercontent.com/jesseconnell/storagebins/master/images/Type_IIIa.png "TypeIIIa - D s s"
[TypeIIIb]: https://raw.githubusercontent.com/jesseconnell/storagebins/master/images/Type_IIIb.png "TypeIIIb - s D s"
[TypeIIIc]: https://raw.githubusercontent.com/jesseconnell/storagebins/master/images/Type_IIIc.png "TypeIIIc - s s D"
[TypeIg]: https://raw.githubusercontent.com/jesseconnell/storagebins/master/images/Type_Ig.png "TypeIg"
[TypeIIg]: https://raw.githubusercontent.com/jesseconnell/storagebins/master/images/Type_IIg.png "TypeIIg"
[TypeIIIg]: https://raw.githubusercontent.com/jesseconnell/storagebins/master/images/Type_IIIg.png "TypeIIIg"
[Rack]: https://raw.githubusercontent.com/jesseconnell/storagebins/master/images/Rack.png "Rack"
