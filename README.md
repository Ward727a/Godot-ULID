# Godot-ULID
An GDExtension that give you the ability to create ULID.

Based on [ULID C++ by Suyash](https://github.com/suyash/ulid/tree/master).

This extension was created for my project, will do update if I need it.

# How to install
Just move the "bin" folder in the "demo" folder inside your project folder.

# How to use
Once the extension is installed, 2 new classes will be available:
- ULIDWrapper
- GDULID

Do not create any ULIDWrapper yourself, this is a class that is reserved by the extension, and is useless if not created by the extension.

To create a ULIDWrapper, use "GDULID" like that:
```GDSCRIPT
func ready():
  # Create a ULIDWrapper
  var rng_key: int = randi_range(1, 128)
  var wrapper: ULIDWrapper = GDULID.Create(rng_key)

  # You can now use the wrapper with the other function available in "GDULID"

  # Convert the ULID to a string
  var str_ulid: String = GDULID.ToString(wrapper)
  print("ULID as string: %s" % str_ulid)

  # Convert the ULID to a PackedByteArray
  var PBA_ulid: PackedByteArray = GDULID.ToBinary(wrapper)
  print("ULID as PBA: %s" % PBA_ulid)

  # Convert an valid ULID string to a ULIDWrapper
  var ulid_from_string: ULIDWrapper = GDULID.FromString(str_ulid)

  # Convert a valid ULID PBA to an ULIDWrapper
  var ulid_from_PBA: ULIDWrapper = GDULID.FromBinary(PBA_ulid)

  # Compare 2 ULID Wrapper
  var compared_ulid: int = GDULID.CompareULIDS(ulid_from_string, ulid_from_PBA)

  # For a complete control over the compare
  match (compared_ulid):
    -1:
      print("ulid_from_string Lexycographically before ulid_from_PBA")
    0:
      print("ulid_from_string same as ulid_from_PBA")
    1:
      print("ulid_from_string lexycographically after ulid_from_PBA")

  # For a more simpler way
  if (compared_ulid != 0):
    print("ulid_from_string and ulid_from_PBA are not the same")
  else:
    print("ulid_from_string and ulid_from_PBA are the same")
```

The other functions available in GDULID are more complexe, and are the same than what you can find in the [ULID C++](https://github.com/suyash/ulid/tree/master) so check there for more info.
