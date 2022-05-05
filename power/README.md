# Power

* Overview:
  * To implement power, we have 2 template partial specialisation.
    * One for base case `n=0`
    * All other case `n > 0`
  * We use an extra template argument `Enable` that will defaults to void (base case).
    * For odd and even `n` case, `Enable` will be substituted using `enable_if_t`.
* SFINAE:
  * For power function we will need to use SFINAE as the function to compute when `n` is even or odd is different.
  * `enable_if_t`: enable if uses SFINAE by having a substitution error if the template argument is false else will substitute it
  `enable_if_t` with the type.
    * For this example, the type does not matter. We only can on invoking the substitution failure.
  * Applying to `pow`:
    * `n` is even:
      * Only the template with `enable_if_t<n % 2 == 0 && n != 0>` will not have substitution failure.
      * The odd template specialisation will have substitution failure.
      * The base case template specialisation will not be used as `n != 0`
    * `n` is odd:
      * Only the template with `enable_if_t<n % 2 != 0 >` will not have substitution failure.
      * The even template specialisation will have substitution failure.
      * The base case template specialisation will not be used as `n != 0`
    * `n = 0`:
      * Both the odd and even template will have substitution failure.
      * This will leave the compiler with only the base case partial specialisation which is
      valid as `n = 0`.


