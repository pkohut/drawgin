# Support and Planned Feature Status #
```
(R = read (stable),   W = write (stable),   - = Not supported)
(r = read (unstable), w = write (unstable), - = Not supported)
```
| **bit code data types** | **R\_13 - R\_2010**|
|:------------------------|:-------------------|
| B :bit                  | R-                 |
| BB :2 bits              | R-                 |
| BS :bitshort            | R-                 |
| BL :bitlong             | R-                 |
| BD :bitdouble           | R-                 |
| 2BD :2D point           | R-                 |
| 3BD :3D point           | R-                 |
| RC :raw char            | R-                 |
| RS :raw short           | R-                 |
| RD :raw double          | R-                 |
| RL :raw long            | R-                 |
| 2RD :2 raw doubles      | R-                 |
| 3RD :3 raw doubles      | R-                 |
| MC  :modular char       | r-                 |
| MS  :modular short      | r-                 |
| H   :handle reference   | R-                 |
| T   :text               | R-                 |
| TU  :unicode text       | R-                 |
| TV  :variable text      | R-                 |
| X   :special form       | --                 |
| SN  :16 byte sentinel   | R-                 |
| BE  :bit extrusion      | r-                 |
| DD  :bit double w/dflt  | --                 |
| BT  :bit thickness      | r-                 |
| 3DD :3D point           | --                 |
| CMC :CmColor value      | R-                 |

| **.dwg file**           | **R\_13** | **R\_14** | **R\_2000** | **R\_2004** | **R\_2007** | **R\_2010** |
|:------------------------|:----------|:----------|:------------|:------------|:------------|:------------|
| file header             | r-        | R-        | r-          | --          | --          | --          |
| Preview Image           | r-        | R-        | r-          | --          |             |             |
| dwg Header Variables    | r-        | R-        | r-          | --          |             |             |

| **Object Types**        | **R\_13** | **R\_14** | **R\_2000** | **R\_2004** | **R\_2007** | **R\_2010** |
|:------------------------|:----------|:----------|:------------|:------------|:------------|:------------|
| Handle                  | r-        | R-        | r-          | --          | --          | --          |