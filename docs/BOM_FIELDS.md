# BOM and sourcing fields (VXDash main board)

Every fitted part on the VXDash board carries the same set of hidden symbol fields.

| Field | Meaning |
|---|---|
| `MFT` | Manufacturer of the design reference part |
| `MFT_PN` | Manufacturer part number of the design reference part |
| `LCSC` | LCSC listing that is the same part as `MFT_PN` (`N/A` when LCSC does not list it) |
| `LCSC alt` | An alternative LCSC part, where one is known |
| `JLCPCB` | Part to use for JLCPCB assembly: a Basic part if one is equal or better in spec, else a Preferred part (no extended-part fee), else the best-stocked Extended part |
| `PBX_MFT` | Manufacturer of the matching PartsBox inventory entry (blank if none) |
| `PBX_PN` | Part number of the matching PartsBox inventory entry (blank if none) |
| `Description` | One pattern per part type, based on the LCSC listing (e.g. `Thick film resistor 10kΩ ±1% 100mW 0603`, `MLCC 100nF 50V X7R ±10% 0603`) |

## Rules

- A PartsBox match means an exact MPN or LCSC number match. No matching by spec.
- A JLCPCB substitute must be equal or better: same value and package, tolerance, power and voltage at least as good, X7R never replaced by X5R.
- Retired fields: `AISLER_MPN`, `ALT_MFT_PN_1`, `JLCPCB extended`, `Recommended JLCPCB`.

## Symbol libraries

The board uses the project libraries in [Lib/sym](../KiCad%20PCB%20Files/Lib/sym) for every component.
Only generic connectors, test points, solder jumpers, mounting holes and power symbols come from the stock KiCad libraries.

| Library | Content |
|---|---|
| `VXDash_passives` | Res, Cap_MLCC, Cap_Pol, Ind, FerriteBead, Polyfuse |
| `VXDash_diodes` | Schottky, zener, TVS and ESD parts, LEDs |
| `VXDash_transistors` | Q_PMOS_GSD, Q_NMOS_GSD, BC857 |
| `VXDash_ICs` | ICs and modules |
| `VXDash_regulators` | AP62200 |
| `VXDash_connectors` | Board-specific connectors |
| `VXDash_electromech` | Buzzer, SW_Push |

Generic symbols (Res, Cap_MLCC, Ind, D_Schottky, D_Zener, LED_Small, the MOSFETs, Buzzer, SW_Push) keep sourcing values per placement.
Part-specific symbols carry the VXDash board values in the library too.
