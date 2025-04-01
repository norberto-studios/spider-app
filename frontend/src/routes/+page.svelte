<script>
    import { Canvas, T } from '@threlte/core'
</script>

<h1>Welcome to SvelteKit</h1>
<p>Visit <a href="https://svelte.dev/docs/kit">svelte.dev/docs/kit</a> to read the documentation</p>

<Canvas>
    <T.Mesh position.y={1}>
        <T.BoxGeometry args={[1, 2, 1]} />
        <T.MeshBasicMaterial color="hotpink" />
    </T.Mesh>
</Canvas>