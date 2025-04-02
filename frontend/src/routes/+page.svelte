<script>
    import {Canvas, T} from '@threlte/core'
    // Import additional helpers
    import {OrbitControls} from '@threlte/extras'

    import AngleSlider from './../lib/AngleSliderComponent.svelte';
    import ModelGroup from './../lib/GltfModelLoaderComponent.svelte';


    const legsController = [1, 2, 3, 4, 5, 6, 7, 8]

    let selectedLegs = $state(legsController[0]);

    $effect(() => {
        console.log("Selected legs:", selectedLegs);
    });

    function handleShapeChange(event) {
        selectedLegs = Number(event.target.value);
        console.log(selectedLegs)
    }

    function angleToRadians(angle) {
        return angle * (Math.PI / 180);
    }

    let angle1 = $state(0); // Default to middle value (90)
    let angle2 = $state(0); // Default to middle value (90)
    let angle3 = $state(0); // Default to middle value (90)
    // Using $derived to compute the rotation in radians
    let rotation1Z = $derived(-angleToRadians(angle1));
    let rotation2X = $derived(-angleToRadians(angle2));
    let rotation3X = $derived(-angleToRadians(angle3));

    // Offset positions for stacking the boxes
    const offset2 = 2; // Distance from hotpink to red
    const offset3 = 2; // Distance from red to yellow

    function handleAngleChange(event) {
        if (event.target.id == 0) {
            angle1 = Number(event.target.value);
        } else if (event.target.id == 1) {
            angle2 = Number(event.target.value);
        } else if (event.target.id == 2) {
            angle3 = Number(event.target.value);
        }
    }

    // Box dimensions - making these explicit for pivot calculations
    const boxWidth = 1;
    const boxHeight = 2;
    const boxDepth = 1;

    // Reference to the pivot group for the transform controls
    let hotpinkGroupRef = $state(null);
    let redGroupRef = $state(null);
    let yellowGroupRef = $state(null);

    function setHotpinkGroupRef(ref) {
        hotpinkGroupRef = ref;
    }

    function setRedGroupRef(ref) {
        redGroupRef = ref;
    }

    function setYellowGroupRef(ref) {
        yellowGroupRef = ref;
    }


    // Function to handle transform controls changes
    function handleGizmoChange(event) {
        // Determine which box is being rotated and log information
        let targetName = "unknown";
        let rotationValues = {};

        if (event.target.object === hotpinkGroupRef) {
            targetName = "Hotpink";
            rotationValues = {
                x: hotpinkGroupRef.rotation.x,
                y: hotpinkGroupRef.rotation.y,
                z: hotpinkGroupRef.rotation.z
            };
        } else if (event.target.object === redGroupRef) {
            targetName = "Red";
            rotationValues = {
                x: redGroupRef.rotation.x,
                y: redGroupRef.rotation.y,
                z: redGroupRef.rotation.z
            };
        } else if (event.target.object === yellowGroupRef) {
            targetName = "Yellow";
            rotationValues = {
                x: yellowGroupRef.rotation.x,
                y: yellowGroupRef.rotation.y,
                z: yellowGroupRef.rotation.z
            };
        }

        console.log(`${targetName} Box Rotated:`);
        console.log(`X: ${(rotationValues.x * 180 / Math.PI).toFixed(2)}°`);
        console.log(`Y: ${(rotationValues.y * 180 / Math.PI).toFixed(2)}°`);
        console.log(`Z: ${(rotationValues.z * 180 / Math.PI).toFixed(2)}°`);
    }

    let activeTransformObject = $state(null);

    function setActiveTransform(object) {
        activeTransformObject = object;
    }


</script>

<div class="text-6xl mb-6">
    <h1>Welcome To Spider App</h1>
</div>
<div class="flex items-start justify-evenly h-screen">
    <div class="text-xl w-full pl-8 pt-8 flex flex-col items-center">
        <h1>Manual Controller</h1>
        <select
                class="w-1/2 px-3 py-2 bg-white border border-gray-300 rounded-md shadow-sm focus:outline-none focus:ring-2 focus:ring-blue-500 focus:border-blue-500"
                onchange={handleShapeChange}
                value={selectedLegs}

        >
            {#each legsController as leg}
                <option value={leg}>{leg} Leg</option>
            {/each}
        </select>

        <AngleSlider
                label="Angle"
                max={90}
                min={-90}
                on:change={handleAngleChange}
                sliderId={0}
                title="Servo 1"
                value={angle1}
        />
        <AngleSlider
                label="Angle"
                max={90}
                min={-90}
                on:change={handleAngleChange}
                sliderId={1}
                title="Servo 2"
                value={angle2}
        />
        <AngleSlider
                label="Angle"
                max={90}
                min={-90}
                on:change={handleAngleChange}
                sliderId={2}
                title="Servo 3"
                value={angle3}
        />

    </div>


    <!--    Display 3D -->
    <!--    <Canvas>-->
    <!--        <T.Mesh rotation.z={0} rotation.y={rotationY}>-->
    <!--            <T.BoxGeometry args={[1, 2, 1]} />-->
    <!--            <T.MeshBasicMaterial color="hotpink" />-->
    <!--        </T.Mesh>-->
    <!--    </Canvas>-->

    <div class="w-full h-1/2">
        <h1>3D Model</h1>
    <Canvas>
        <!-- Camera setup first -->
        <T.PerspectiveCamera
                fov={75}
                makeDefault
                position={[0, 3, 12]}

        >
            <!-- OrbitControls must be a child of a Camera -->
<!--            <OrbitControls/>-->
        </T.PerspectiveCamera>

        <!--{/* Parent group for pivot control */}-->
        <T.Group position={[0, 0, -3]} rotation.x={angleToRadians(90)}>
            <ModelGroup
                    boxSize={[boxWidth, boxHeight, boxDepth]}
                    fallbackColor="hotpink"
                    fallbackWireframe={false}
                    modelPath={''}
                    modelScale={[0.5, 0.5, 0.5]}
                    rotationZ={rotation1Z}
                    setGroupRef={setHotpinkGroupRef}
            >

                <ModelGroup
                        boxSize={[boxWidth, boxHeight, boxDepth]}
                        fallbackColor="red"
                        fallbackWireframe={false}
                        modelPath={''}
                        modelScale={[0.5, 0.5, 0.5]}
                        positionY={boxHeight}
                        rotationX={rotation2X}
                        setGroupRef={setRedGroupRef}
                >

                    <ModelGroup
                            boxSize={[boxWidth, boxHeight + 2, boxDepth]}
                            fallbackColor="yellow"
                            fallbackWireframe={false}
                            modelPath={''}
                            modelScale={[0.5, 0.5, 0.5]}
                            positionY={boxHeight}
                            rotationX={rotation3X}
                            setGroupRef={setYellowGroupRef}
                    />
                </ModelGroup>
            </ModelGroup>
        </T.Group>

        <!--        &lt;!&ndash; Transform Controls that targets the active object &ndash;&gt;-->
        <!--        {#if activeTransformObject}-->
        <!--            <TransformControls-->
        <!--                    object={activeTransformObject}-->
        <!--                    mode="rotate"-->
        <!--                    on:objectChange={handleGizmoChange}-->
        <!--            />-->
        <!--        {/if}-->


        <!-- Axis helper for coordinate visualization -->
        <T.AxesHelper args={[5]}/>

        <!-- Grid helper for better visualization -->
        <T.GridHelper args={[10, 10]}/>

    </Canvas>
    </div>
</div>
