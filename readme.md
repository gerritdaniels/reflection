
# Definition

This is a header only library that defines a macro for adding reflection information to a class. This reflection 
information can optionally be used to define a boost::serialization serialize method inside the class.

# Dependencies

This library depends on boost::mpl and boost::preprocessor. The REFLECTED_SERIALIZATION() macro depends on
boost::serialization.

# Usage

The macro to use is REFLECTION. Its first argument is the class name, the second argument is a boost::preprocessor 
sequence defining the base classes and members. 

Base classes are defined as a boost::preprocessor tuple of two arguments: the access specifier and the base class type.

Members are defined as a boost::preprocessor tuple of three arguments: the access specifier, the type and the variable 
name. When defining a member it also gets declared, so no separate declaration is needed. 


``` cpp
class DerivedClass : public SimpleClass {

    REFLECTION(DerivedClass,
        ((public, SimpleClass))
        ((private, int, count))
        ((protected, std::string, name))
    )
    
};
```

# Reflection information

The REFLECTION macro creates two typedefs: base_classes and members. These are both boost::mpl::vector instantiations,
holding all the base class reflection information and member reflection information respectively.

## Base class reflection information

From the reflection information of a base class you can access the following:

`Type`

> A typedef for the actual base class type.

`static const char* type()`

> A static method that returns the type name as supplied by `typeid(Type).name()`.

`static const char* access`

> The access specifier as string.

## Member reflection information

From the reflection information of a member you can access the following:

`Type`

> A typedef for the actual member type.

`static const char* type()`

> A static method that returns the type name as supplied by `typeid(Type).name()`.

`static const char* access`

> The access specifier as string.

`static const char* name`

> The name of the member variable.

`static Type& get(ContainingClass& c)`

> Returns a reference to the member when supplied with a reference to the containing class.

`static const Type& get(const ContainingClass& c)`

> Returns a const reference to the member when supplied with a const reference to the containing class.

# Serialization

The macro REFLECTED_SERIALIZATION implements a boost::serialization serialize method using the reflection information.
If you want to use polymorphic pointers you will need to use the boost::serialization macro BOOST_CLASS_EXPORT.

``` cpp
class DerivedClass : public SimpleClass {

    REFLECTION(DerivedClass,
        ((public, SimpleClass))
        ((private, int, count))
        ((protected, std::string, name))
    )
    
    REFLECTED_SERIALIZATION()
};
```

