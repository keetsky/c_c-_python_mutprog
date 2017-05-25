
next 	up 	previous 	Extending and Embedding the Python Interpreter 	contents 		
Next: 1.8 Keyword Parsing with Up: 1. Extending Python with Previous: 1.6 Calling Python Functions

1.7 Format Strings for PyArg_ParseTuple()

The PyArg_ParseTuple() function is declared as follows:

    int PyArg_ParseTuple(PyObject *arg, char *format, ...);

The arg argument must be a tuple object containing an argument list passed from Python to a C function. The format argument must be a format string, whose syntax is explained below. The remaining arguments must be addresses of variables whose type is determined by the format string. For the conversion to succeed, the arg object must match the format and the format must be exhausted.

Note that while PyArg_ParseTuple() checks that the Python arguments have the required types, it cannot check the validity of the addresses of C variables passed to the call: if you make mistakes there, your code will probably crash or at least overwrite random bits in memory. So be careful!

A format string consists of zero or more ``format units''. A format unit describes one Python object; it is usually a single character or a parenthesized sequence of format units. With a few exceptions, a format unit that is not a parenthesized sequence normally corresponds to a single address argument to PyArg_ParseTuple(). In the following description, the quoted form is the format unit; the entry in (round) parentheses is the Python object type that matches the format unit; and the entry in [square] brackets is the type of the C variable(s) whose address should be passed. (Use the "&"operator to pass a variable's address.)

Note that any Python object references which are provided to the caller are borrowed references; do not decrement their reference count!

"s" (string) [char *]
    Convert a Python string to a C pointer to a character string. You must not provide storage for the string itself; a pointer to an existing string is stored into the character pointer variable whose address you pass. The C string is null-terminated. The Python string must not contain embedded null bytes; if it does, a TypeError exception is raised.

"s#" (string) [char *, int]
    This variant on "s" stores into two C variables, the first one a pointer to a character string, the second one its length. In this case the Python string may contain embedded null bytes.

"z" (string or None) [char *]
    Like "s", but the Python object may also be None, in which case the C pointer is set to NULL.

"z#" (string or None) [char *, int]
    This is to "s#" as "z" is to "s".

"b" (integer) [char]
    Convert a Python integer to a tiny int, stored in a C char.

"h" (integer) [short int]
    Convert a Python integer to a C short int.

"i" (integer) [int]
    Convert a Python integer to a plain C int.

"l" (integer) [long int]
    Convert a Python integer to a C long int.

"c" (string of length 1) [char]
    Convert a Python character, represented as a string of length 1, to a C char.

"f" (float) [float]
    Convert a Python floating point number to a C float.

"d" (float) [double]
    Convert a Python floating point number to a C double.

"D" (complex) [Py_complex]
    Convert a Python complex number to a C Py_complex structure.

"O" (object) [PyObject *]
    Store a Python object (without any conversion) in a C object pointer. The C program thus receives the actual object that was passed. The object's reference count is not increased. The pointer stored is not NULL.

"O!" (object) [typeobject, PyObject *]
    Store a Python object in a C object pointer. This is similar to "O", but takes two C arguments: the first is the address of a Python type object, the second is the address of the C variable (of type PyObject *) into which the object pointer is stored. If the Python object does not have the required type, TypeError is raised.

"O&" (object) [converter, anything]
    Convert a Python object to a C variable through a converter function. This takes two arguments: the first is a function, the second is the address of a C variable (of arbitrary type), converted to void *. The converter function in turn is called as follows:

    status = converter(object, address);

    where object is the Python object to be converted and address is the void * argument that was passed to PyArg_ConvertTuple(). The returned status should be 1 for a successful conversion and 0 if the conversion has failed. When the conversion fails, the converter function should raise an exception.

"S" (string) [PyStringObject *]
    Like "O" but requires that the Python object is a string object. Raises TypeError if the object is not a string object. The C variable may also be declared as PyObject *.

"(items)" (tuple) [matching-items]
    The object must be a Python sequence whose length is the number of format units in items. The C arguments must correspond to the individual format units in items. Format units for sequences may be nested.

    Note: Prior to Python version 1.5.2, this format specifier only accepted a tuple containing the individual parameters, not an arbitrary sequence. Code which previously caused TypeError to be raised here may now proceed without an exception. This is not expected to be a problem for existing code.

It is possible to pass Python long integers where integers are requested; however no proper range checking is done -- the most significant bits are silently truncated when the receiving field is too small to receive the value (actually, the semantics are inherited from downcasts in C -- your mileage may vary).

A few other characters have a meaning in a format string. These may not occur inside nested parentheses. They are:

"|"
    Indicates that the remaining arguments in the Python argument list are optional. The C variables corresponding to optional arguments should be initialized to their default value -- when an optional argument is not specified, PyArg_ParseTuple() does not touch the contents of the corresponding C variable(s).

":"
    The list of format units ends here; the string after the colon is used as the function name in error messages (the ``associated value'' of the exception that PyArg_ParseTuple() raises).

";"
    The list of format units ends here; the string after the colon is used as the error message instead of the default error message. Clearly, ":" and ";" mutually exclude each other.

Some example calls:

        int ok;
        int i, j;
        long k, l;
        char *s;
        int size;

        ok = PyArg_ParseTuple(args, ""); /* No arguments */
            /* Python call: f() */

        ok = PyArg_ParseTuple(args, "s", &s); /* A string */
            /* Possible Python call: f('whoops!') */

        ok = PyArg_ParseTuple(args, "lls", &k, &l, &s); /* Two longs and a string */
            /* Possible Python call: f(1, 2, 'three') */

        ok = PyArg_ParseTuple(args, "(ii)s#", &i, &j, &s, &size);
            /* A pair of ints and a string, whose size is also returned */
            /* Possible Python call: f((1, 2), 'three') */

        {
            char *file;
            char *mode = "r";
            int bufsize = 0;
            ok = PyArg_ParseTuple(args, "s|si", &file, &mode, &bufsize);
            /* A string, and optionally another string and an integer */
            /* Possible Python calls:
               f('spam')
               f('spam', 'w')
               f('spam', 'wb', 100000) */
        }

        {
            int left, top, right, bottom, h, v;
            ok = PyArg_ParseTuple(args, "((ii)(ii))(ii)",
                     &left, &top, &right, &bottom, &h, &v);
            /* A rectangle and a point */
            /* Possible Python call:
               f(((0, 0), (400, 300)), (10, 10)) */
        }

        {
            Py_complex c;
            ok = PyArg_ParseTuple(args, "D:myfunction", &c);
            /* a complex, also providing a function name for errors */
            /* Possible Python call: myfunction(1+2j) */
        }

next 	up 	previous 	Extending and Embedding the Python Interpreter 	contents 		
Next: 1.8 Keyword Parsing with Up: 1. Extending Python with Previous: 1.6 Calling Python Functions
Send comments on this document to python-docs@python.org.

