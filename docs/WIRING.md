# Conditional switching guidance

This is guidance for review, not a recovered schematic. Do not wire directly from the photo.

For a mouse whose button connects a positive, low-voltage logic signal to mouse ground, a suitably rated NPN switch can sometimes operate in parallel with that button: emitter to verified mouse ground, collector to the verified signal contact, and base driven through a calculated current-limiting resistor. This arrangement requires an appropriate shared reference between controller and mouse. A base-emitter pull-down can help keep the transistor off during reset. Validate the complete circuit first.

Do not apply this arrangement to a scanned switch matrix, unknown polarity, or a contact above the transistor/controller ratings. Measure the open and closed button voltages with the real mouse before choosing an interface; use an appropriately rated isolated interface if needed. Never feed USB 5 V into an ESP32 GPIO.

2N2222/PN2222 package pin orders vary. Consult the datasheet for the exact part and package instead of assuming the flat-face orientation. Determine resistor values from the required collector current and GPIO/base-current limits; the photo does not establish them.

Disconnect power for soldering, check for shorts, provide insulation and strain relief, and verify that manual mouse clicking still works. Leave the reference sketch in simulation mode until the GPIO, transistor polarity and circuit are confirmed.
