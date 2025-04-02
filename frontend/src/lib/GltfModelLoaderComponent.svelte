<script>
    import { T, useLoader } from '@threlte/core'
    import { GLTFLoader } from 'three/examples/jsm/loaders/GLTFLoader.js'
    import * as THREE from 'three'
    import { onMount } from 'svelte'

    // Props using $props() runes syntax for Svelte 5
    const {
        // Model configuration
        modelPath = '',
        modelScale = [0.5, 0.5, 0.5],

        // Fallback configuration
        fallbackColor = 'yellow',
        fallbackWireframe = true,
        boxSize = [1, 2, 1],

        // Positioning
        positionY = 0,
        positionX = 0,

        // Rotation
        rotationX = 0,
        rotationY = 0,
        rotationZ = 0,

        // Pivot point configuration
        pivotColor = 'blue',
        pivotOpacity = 0.7,
        pivotSize = 0.1,

        // Callbacks
        onModelLoaded = null,

        // Group reference setter function instead of bindable
        setGroupRef = () => {}
    } = $props();

    // Local state using runes
    let model = $state(null);
    let loading = $state(true);
    let error = $state(null);
    let progress = $state(0);

    // Local ref to handle in this component
    let localGroupRef = $state(null);

    // Update the parent reference when our local reference changes
    $effect(() => {
        if (localGroupRef) {
            setGroupRef(localGroupRef);
        }
    });

    // Destructure box dimensions for readability
    const [boxWidth, boxHeight, boxDepth] = boxSize;

    // Handle model loading if a path is provided
    $effect(() => {
        if (!modelPath) return;

        // Only load the model if a path is provided
        try {
            model = useLoader(GLTFLoader, modelPath);

            // Process model when loaded
            if (model) {
                // Make any adjustments to the model here
                model.scene.traverse((node) => {
                    if (node.isMesh) {
                        // Enable shadows
                        node.castShadow = true;
                        node.receiveShadow = true;
                    }
                });

                loading = false;

                if (onModelLoaded) {
                    onModelLoaded(model);
                }
            }
        } catch (err) {
            error = err.message || 'Failed to load model';
            loading = false;
            console.error('Model loading error:', err);
        }
    });

    // Alternative loading approach with progress tracking
    onMount(() => {
        if (!modelPath || model) return;

        const loader = new GLTFLoader();

        loader.load(
            modelPath,
            (gltf) => {
                model = gltf;
                loading = false;
                if (onModelLoaded) onModelLoaded(model);
            },
            (xhr) => {
                if (xhr.lengthComputable) {
                    progress = (xhr.loaded / xhr.total) * 100;
                }
            },
            (err) => {
                error = err.message || 'Failed to load model';
                loading = false;
                console.error('Model loading error:', err);
            }
        );
    });
</script>

<T.Group
        ref={node => { localGroupRef = node; }}
        position={[positionX, positionY, 0]}
        rotation.x={rotationX}
        rotation.y={rotationY}
        rotation.z={rotationZ}
>
    <!-- Pivot point indicator -->
    <T.Mesh position={[0, 0, 0]}>
        <T.SphereGeometry args={[pivotSize, 16, 16]} />
        <T.MeshBasicMaterial color={pivotColor} transparent opacity={pivotOpacity} />
    </T.Mesh>

    <!-- Model or fallback -->
    {#if model && !loading && !error}
        <T.Primitive
                object={model.scene.clone()}
                position={[0, boxHeight/2, 0]}
                scale={modelScale}
        />
    {:else if error}
        <!-- Error fallback -->
        <T.Mesh position={[0, boxHeight/2, 0]}>
            <T.BoxGeometry args={[boxWidth, boxHeight, boxDepth]} />
            <T.MeshBasicMaterial color="red" wireframe={true} />
        </T.Mesh>
        <!-- Optional: Display error text -->
        <T.Mesh position={[0, boxHeight + 0.5, 0]}>
            <T.SphereGeometry args={[0.2, 16, 16]} />
            <T.MeshBasicMaterial color="red" />
        </T.Mesh>
    {:else}
        <!-- Loading fallback -->
        <T.Mesh position={[0, boxHeight/2, 0]}>
            <T.BoxGeometry args={[boxWidth, boxHeight, boxDepth]} />
            <T.MeshBasicMaterial color={fallbackColor} wireframe={fallbackWireframe} />
        </T.Mesh>
    {/if}

    <!-- Optional loading indicator -->
    {#if loading && progress > 0}
        <T.Group position={[0, boxHeight + 0.5, 0]}>
            <T.Mesh rotation.x={Math.PI / 2}>
                <T.RingGeometry args={[0.3, 0.4, 32]} />
                <T.MeshBasicMaterial color="#333333" />
            </T.Mesh>
            <T.Mesh rotation.x={Math.PI / 2}>
                <T.RingGeometry args={[0.3, 0.4, 32, 1, 0, (progress / 100) * Math.PI * 2]} />
                <T.MeshBasicMaterial color="#00aaff" />
            </T.Mesh>
        </T.Group>
    {/if}

    <!-- Slot for additional child elements -->
    <slot></slot>
</T.Group>
